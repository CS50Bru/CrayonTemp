

//NB !!! You have to define VK_USE_PLATFORM_WIN32_KHR in your project's preprocessor definitions
#define VMA_IMPLEMENTATION

#include<fstream>
#include<ranges>
//you have to include Windows.h before vulkan.h because Vulkan needs HWND etc.
#include<Windows.h>
#include<vulkan/vulkan.h>
#include<vulkan/vulkan_win32.h>
#include<vector>

#include"Core.h"
#include"Renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include"Libraries/stb/stb_image.h"


namespace Crayon
{
    Renderer::~Renderer()
    {
        cleanUp();
    }

    AttachmentGroup Renderer::getUiRenderpassInfo() const
    {
        AttachmentGroup uiAttachments{};
        uiAttachments.mainAttachmentFormat = STAGING_IMAGE_FORMAT;
        uiAttachments.depthBufferFormat = DEPTH_BUFFER_DEFAULT_FORMAT;

        return uiAttachments;
        
    }


int Renderer::init( HWND winHandle,  glm::uvec2 screenExtent, const std::unordered_map<std::string, std::string>& editorSettings)
{
    m_cameraBufferDescriptorSlot = std::make_shared<DescriptorSlot>();
    m_textureArrayDescriptorSlot = std::make_shared<DescriptorSlot>();
    m_spriteBufferDescriptorSlot = std::make_shared<DescriptorSlot>();
    m_preprocessedImageBufferDescriptorSlot = std::make_shared<DescriptorSlot>();
    m_currentFrameNumber = 0;

    

    setScreenExtent( screenExtent.x, screenExtent.y );

    //-----------------------------------------------------------------------
    createVulkanInstance( m_vkInstance);

#ifdef DEBUG
    setUpVulkanDebugMessenger();
#endif // DEBUG


    //-------------------------------------------------------------------------
    //Now let's set up our SURFACE (a reference to our window, basically)

    createSurface( winHandle, m_vkInstance, m_surface );

    //choose a physical device, and find the queue family on it that handles graphics
    //sets up m_physDevProperties and m_physDev
    initPhysicalDevice();

    //now that we know about the graphics queue etc., we can set up the logical device
    createLogicalDevice();

    //Get the maximum number of output vertices per mesh shader invocation
    //The familiar chainging pattern here: VkPhsycialDeviceProperties2 doesn't directly have a field for 'mesh shader properties', but you can chain a VkPhyscialDeviceMeshShaderPorpeortiesEXT struct to it
    VkPhysicalDeviceMeshShaderPropertiesEXT meshProps = {};
    meshProps.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
    meshProps.pNext = nullptr; 
    
        VkPhysicalDeviceProperties2 props = {};
        props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        props.pNext = &meshProps;

        vkGetPhysicalDeviceProperties2( m_physDev, &props );

        CRAYON_ASSERT( meshProps.maxMeshOutputVertices >= meshShaderMaxVertexOutput );
        CRAYON_ASSERT( meshProps.maxMeshOutputPrimitives >= meshShaderMaxPrimitiveOutput );


    //Dynamically load external functions
    //NB MUST BE DONE AFTER CREATION OF LOGICAL DEVICE
    //The reason for this dynamic loading approach is that different drivers or platforms might implement extensions differently, or might not support them at all. By loading the function pointers at runtime, your program can adapt to what's actually available on the system where it's running.
    m_vkCmdDrawMeshTasksEXT = (PFN_vkCmdDrawMeshTasksEXT)vkGetDeviceProcAddr( m_logDev, "vkCmdDrawMeshTasksEXT" );
    CRAYON_ASSERT( m_vkCmdDrawMeshTasksEXT != nullptr );



    //Create swapchain
    createSwapChain( winHandle );

    setUpGraphicsQueueCommandPoolsAndBuffers( m_logDev, m_graphicsFamilyIndex, m_graphicsQueue, m_frameDataStructs );

    //set up synchronization
    createSemaphores( m_logDev, m_frameDataStructs, 0 );


    setUpAllocatorThenResourcesAndDescriptorSets();

    //set up image resources
    //ToDo: this should be done together with where we set up the actual staging images etc., but that can wait until the resource management rework

    for ( auto& frameDataStruct : m_frameDataStructs )
    {
        frameDataStruct.preprocessingImage.baseMipLevel = 0;
        frameDataStruct.preprocessingImage.aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
        frameDataStruct.preprocessingImage.levelCount = 1;
        frameDataStruct.preprocessingImage.baseArrayLayer = 0;
        frameDataStruct.preprocessingImage.layerCount = 1;
        frameDataStruct.preprocessingImage.currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    }

    
    setUpPipelines();


    //set up index buffer for sprite pipeline
    m_indicesForIndexBuffer = { 0,1,2,2,3,0 };
    setUpIndexBuffer( m_quadIndexBuffer,m_indicesForIndexBuffer );


    //To Do: bug.
    //For some reason, you have to wait until this point in init before you change the camera position... something at some point is using m_cameraPosition when it should just be using {0.f, 0.f}
    m_cameraPosition = { 0.5f * m_screenWidth, 0.5f * m_screenHeight };

   


    return 1;
}
// end of init()

void Renderer::createSemaphores( const VkDevice& logDev, std::vector<FrameData>& frameDataStructs, size_t currentFrameNumber)
{
    for ( size_t i = 0; i < FRAME_OVERLAP; i++ )
    {

        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
       
        
        //Create "image available" semaphore
        VkResult createSemaphoreResult = vkCreateSemaphore( logDev, &semaphoreInfo, nullptr, &frameDataStructs[i].imageAvailableSempahore );
        CRAYON_ASSERT( createSemaphoreResult == VK_SUCCESS );

        //Create "image rendererd to" semaphore
        createSemaphoreResult = vkCreateSemaphore( logDev, &semaphoreInfo, nullptr, &frameDataStructs[i].imageRenderedToSemaphore );
        CRAYON_ASSERT( createSemaphoreResult == VK_SUCCESS );
        

        //Create 'commandBufferFree' sempahore (it's a timeline sempahore so there's a little bit of extra info)
        //A timeline semaphore for host-device sync (making sure that the gpu is done with the command buffer before the cpu resets it)
        VkSemaphoreTypeCreateInfo commandBufferSemaphoreTypeCreateInfo{};
        commandBufferSemaphoreTypeCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
        commandBufferSemaphoreTypeCreateInfo.pNext = nullptr;
        commandBufferSemaphoreTypeCreateInfo.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE;

        VkSemaphoreCreateInfo commandBufferSemaphoreCreateInfo{};
        commandBufferSemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        commandBufferSemaphoreCreateInfo.flags = 0;

        CRAYON_ASSERT( currentFrameNumber == 0 );
        commandBufferSemaphoreTypeCreateInfo.initialValue = currentFrameNumber;

        commandBufferSemaphoreCreateInfo.pNext = &commandBufferSemaphoreTypeCreateInfo;

        createSemaphoreResult = vkCreateSemaphore( logDev, &commandBufferSemaphoreCreateInfo, nullptr, &frameDataStructs[i].commandBufferFreeSemaphore );
        CRAYON_ASSERT( createSemaphoreResult == VK_SUCCESS );
    }
}



//needs setting up to use our actual logger instead
VKAPI_ATTR VkBool32 VKAPI_CALL Renderer::validationDebugCallback( VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData )
{

    // Print different prefixes based on message severity
    switch ( messageSeverity )
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        std::cout << "VERBOSE: ";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        std::cout << "INFO: ";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        std::cout << "WARNING: ";
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        std::cerr << "ERROR: ";
        break;
    default:
        std::cout << "UNKNOWN: ";
        break;
    }

    // Print the actual debug message
    std::cout << pCallbackData->pMessage << std::endl;

    // The return value tells Vulkan if the triggering Vulkan call should be aborted
    // VK_FALSE means "don't abort the call"
    return VK_FALSE;
}

void Renderer::setUpDescriptors()
{
    //to do: given that in the current model we have 1 global superset and 1 binding per set, we could just automate all of the set creation and let the user just create a resource without worrying about the rest of it


    m_globalDescriptorSet = std::make_shared<DescriptorSet>();
    m_globalDescriptorSet->m_name = GLOBAL_DESCRIPTOR_SET_NAME;

    m_stagingImagesDescriptorSet = std::make_shared<DescriptorSet>();
    m_stagingImagesDescriptorSet->m_name = STAGING_IMAGES_DESCRIPTOR_SET_NAME;

    m_textureDescriptorSet = std::make_shared<DescriptorSet>();
    m_textureDescriptorSet->m_name = "TextureDescriptorSet";

    m_spriteBufferDescriptorSet = std::make_shared<DescriptorSet>();
    m_spriteBufferDescriptorSet->m_name = "SpriteBufferDescriptorSet";

    //set up Crayon descriptor groups
   // m_cameraBufferDescriptorSlot = std::make_shared<CrayDescriptorSlot>();
    m_cameraBufferDescriptorSlot->name = CAMERA_BUFFER_SLOT_NAME;
    m_cameraBufferDescriptorSlot->descriptorCount = 1;
    m_cameraBufferDescriptorSlot->baseTypeSize = static_cast<uint32_t>(sizeof( MVP ));
    m_cameraBufferDescriptorSlot->descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    m_cameraBufferDescriptorSlot->usesDynamicAligment = true;
    m_cameraBufferDescriptorSlot->stageFlags = ALL_USED_SHADER_STAGES;
    m_cameraBufferDescriptorSlot->bindingFlags = {};

    m_globalDescriptorSet->addDescriptorSlot( m_cameraBufferDescriptorSlot );

    //m_textureArrayDescriptorSlot = std::make_shared<CrayDescriptorSlot>();
    m_textureArrayDescriptorSlot->name = TEXTURE_ARRAY_SLOT_NAME;
    m_textureArrayDescriptorSlot->descriptorCount = MAX_TEXTURE_COUNT;
    m_textureArrayDescriptorSlot->usesDynamicAligment = false;
    m_textureArrayDescriptorSlot->dynamicAlignment = 0;
    m_textureArrayDescriptorSlot->descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    m_textureArrayDescriptorSlot->stageFlags = ALL_USED_SHADER_STAGES;
    m_textureArrayDescriptorSlot->bindingFlags = VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT;

    m_textureDescriptorSet->addDescriptorSlot( m_textureArrayDescriptorSlot );

  //  m_preprocessedImageBufferDescriptorSlot = std::make_shared<CrayDescriptorSlot>();
    m_preprocessedImageBufferDescriptorSlot->name = UNPROCESSED_IMAGES_SLOT_NAME;
    m_preprocessedImageBufferDescriptorSlot->descriptorCount = FRAME_OVERLAP;
    m_preprocessedImageBufferDescriptorSlot->usesDynamicAligment = false;
    m_preprocessedImageBufferDescriptorSlot->dynamicAlignment = 0;
    m_preprocessedImageBufferDescriptorSlot->descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    m_preprocessedImageBufferDescriptorSlot->stageFlags = ALL_USED_SHADER_STAGES;
    //ToDo: uh, why have I given my preprocessedImageDescriptorSlot the 'variable descriptor count' flag?
    m_preprocessedImageBufferDescriptorSlot->bindingFlags = VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT;
    //ToDo: fix this weird naming disparity between the set and the slot
    m_stagingImagesDescriptorSet->addDescriptorSlot( m_preprocessedImageBufferDescriptorSlot );



     m_spriteBufferDescriptorSlot->name = "SpriteBufferSlot";
     m_spriteBufferDescriptorSlot->descriptorCount = 1;
     m_spriteBufferDescriptorSlot->usesDynamicAligment = false;
     m_spriteBufferDescriptorSlot->dynamicAlignment = 0;
     m_spriteBufferDescriptorSlot->descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
     m_spriteBufferDescriptorSlot->stageFlags = ALL_USED_SHADER_STAGES;
     m_spriteBufferDescriptorSlot->bindingFlags = VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT;



     m_spriteBufferDescriptorSet->addDescriptorSlot( m_spriteBufferDescriptorSlot );
     
     //this defines the order of the sets, and the shader code has to match this
    //To Do: this is fragile. Is there some way we could automate the link through templates etc.?
    m_descriptorSuperset.addDescriptorSet( m_globalDescriptorSet ); //set 0 etc.
    m_descriptorSuperset.addDescriptorSet( m_textureDescriptorSet );
    m_descriptorSuperset.addDescriptorSet( m_stagingImagesDescriptorSet );
    m_descriptorSuperset.addDescriptorSet( m_spriteBufferDescriptorSet );

    ///////////////////////////////////////////////////
    //set up descriptor POOL

    setUpDescriptorPool( m_logDev, m_descriptorSuperset, m_descriptorPool );

   
    ////////////////////////////////////////////////////
    //set up descriptor set LAYOUTS


    for ( auto& set : m_descriptorSuperset.m_sets )
    {
        setUpDescriptorSetLayout( m_logDev, *set );
    }


    allocateToDescriptorSets( m_logDev, m_descriptorPool, m_descriptorSuperset );
}

void Renderer::setUpDepthImages(uint32_t width, uint32_t height, bool useForSampling)
{
    VkFormatProperties formatProperties;

    //this tells you what you can use a certain VkFormat for. It doesn't check DIRECTLY to say 'Oh you can use this as a depth buffer', but for a depth buffer to be remotely performant it has to be able to be used in certain ways: for example, it has to support optimal tiling
    vkGetPhysicalDeviceFormatProperties( m_physDev, DEPTH_BUFFER_DEFAULT_FORMAT, &formatProperties );

    //formatProperties is a bitset, and represents a bunch of different tiling features, such as 'can be sampled', 'can be color buffer' etc.
    if ( !(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) )
    {
        std::cerr << "This GPU cannot use the desired image format as a depth buffer. I don't know what to do." << std::endl;

        abort();
    }



    for ( auto& frameDataStruct : m_frameDataStructs )
    {
        ImageResource& depthImage = frameDataStruct.preprocessingDepthBuffer;

        VkImageUsageFlags usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

        //if you're going to sample from this depth buffer (to use for shadow maps etc.)
        if ( useForSampling )
        {
            usage |= VK_IMAGE_USAGE_SAMPLED_BIT;
        }


       /* depthImage.imageWidth = width;
        depthImage.imageHeight = height;*/
        depthImage.imageDimensions.x = width;
        depthImage.imageDimensions.y = height;
        depthImage.imageFormat = DEPTH_BUFFER_DEFAULT_FORMAT;
            depthImage.viewFormat = depthImage.imageFormat;

        //To Do: maybe we should add 'tiling' as a field in ImageResource
        depthImage.currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthImage.latestUsageStage = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT;
        depthImage.latestAccessType = VK_ACCESS_2_NONE;

        //aspect: data within image that you're wanting to use.
        //to do: This can change depending on the operation you're carrying out, so it might not make that much sense, actually, to bake it into the ImageResource itself
        depthImage.aspectFlags = VK_IMAGE_ASPECT_DEPTH_BIT;
        depthImage.baseMipLevel = 0;
        depthImage.levelCount = 1;
        depthImage.baseArrayLayer = 0;
        depthImage.layerCount = 1;

        createImage( depthImage.imageDimensions.x, depthImage.imageDimensions.y, depthImage.imageFormat, VK_IMAGE_TILING_OPTIMAL, usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage.image, depthImage.imageAllocation );

        depthImage.imageView= createImageView( depthImage.image, depthImage.viewFormat, depthImage.aspectFlags );


    }
}

//To Do: I'd get rid of this function:it's too monolithic, and in any case we're only calling it once, right?
void Renderer::setUpAllocatorThenResourcesAndDescriptorSets()
{
    setUpAllocator( m_vkInstance, m_logDev, m_physDev, m_vmaAllocator );


    setUpPreprocessImages( m_vmaAllocator );


    const ImageResource& stagingImageReference = getCurrentFrame().preprocessingImage;
    setUpDepthImages( stagingImageReference.imageDimensions.x, stagingImageReference.imageDimensions.y, false );

    //set up depth buffers for the preprocess images
    /* Setting up the depth bufers for the preprocess images: 
    
    Not all image formats are usable as depth buffers on all GPUs.
    However, there are some that are very, very commonly used:
    for simple apps, VK_FORMAT_D16_UNORM is pretty common, and Unreal etc. use VK_FORMAT_D24_UNORM_S8_UINT (which also gives you a little stencil baked into the depth buffer that you can then use for other stuff if you want).

    */
   


    //sets up m_textureSampler
    createTextureSampler();

    //set up descriptors
    setUpDescriptors();

    createCameraBufferAndUpdateDescriptorSet();

    //
    const VkDeviceSize spriteBufferSize = MAX_SPRITES * sizeof( Sprite );
   // VkBufferUsageFlags spriteBufferUsage= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    
    createVmaBuffer( spriteBufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, m_spriteBuffer.gpuBuffer, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );

    m_allocatedBuffers.push_back( m_spriteBuffer.gpuBuffer );

 
    createVmaBuffer( spriteBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, m_spriteBuffer.stagingBuffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT );
    m_allocatedBuffers.push_back( m_spriteBuffer.stagingBuffer );

    //next up: have AllocatedBuffers store their size
    




    updateDescriptorSlot( m_logDev, *m_spriteBufferDescriptorSlot, m_spriteBuffer.gpuBuffer.buffer );

 /*       const VkDeviceSize uniformBufferSize = slot.dynamicAlignment * FRAME_OVERLAP;
    createVmaBuffer( uniformBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, m_cameraBuffer, VMA_MEMORY_USAGE_CPU_TO_GPU );
    m_allocatedBuffers.push_back( m_cameraBuffer );

    updateDescriptorSlot( m_logDev, *m_cameraBufferDescriptorSlot, m_cameraBuffer.buffer );*/

    createStorageImagesAndUpdateDescriptorSet();
}

void Renderer::setUpVulkanDebugMessenger()
{
    //PFN: Pointer To Function
    PFN_vkCreateDebugUtilsMessengerEXT debugMessengerCreatorFunctionPointer = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr( m_vkInstance, "vkCreateDebugUtilsMessengerEXT" );

    CRAYON_ASSERT( debugMessengerCreatorFunctionPointer != nullptr );

    VkDebugUtilsMessengerCreateInfoEXT messengerCreateInfo = {};  // Zero initialize
    messengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    messengerCreateInfo.pNext = nullptr;

    messengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |  // Detailed diagnostic info
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |  // Important warnings
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT; // Dangerous errors

    messengerCreateInfo.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |      // General Vulkan info
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |   // Validation layer warnings/errors
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;   // Performance warnings

    messengerCreateInfo.pfnUserCallback = validationDebugCallback;
    messengerCreateInfo.pUserData = nullptr;  // Optional: could pass data to your callback

    debugMessengerCreatorFunctionPointer( m_vkInstance, &messengerCreateInfo, nullptr, &m_debugMessenger );

}

void Renderer::setUpCommandBufferWithDesiredSettings(VkCommandBuffer& commandBuffer, const VkExtent2D& swapchainImageExtent, float screenWidth, float screenHeight)
{
    VkCommandBufferBeginInfo bufferBeginInfo = {};
    bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    //vkGuide: "it’s best if Vulkan knows that this command will only execute once, as it can allow for great optimization by the driver."
    bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    bufferBeginInfo.pInheritanceInfo = nullptr;

    VkResult beginCommandBufferResult = vkBeginCommandBuffer( commandBuffer, &bufferBeginInfo );
    CRAYON_ASSERT( beginCommandBufferResult == VK_SUCCESS );


    ////////////////////////////////////////////////
    //deal with SETTINGS for  command buffer
    VkViewport viewport = {};
    //vulkanTutorial: "A viewport basically describes the region of the framebuffer that the output will be rendered to.
    //This will almost always be( 0, 0 ) to( width, height ) and in this tutorial that will also be the case."
    //In other words, the viewport will squash your image into the top half of the screen  if you want it to
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(screenWidth);
    viewport.height = static_cast<float>(screenHeight);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport( commandBuffer, 0, 1, &viewport );

    //where the viewport squashes (transforms) your image into part of the framebuffer, the scissor cuts parts of it off
    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = swapchainImageExtent;
    vkCmdSetScissor( commandBuffer, 0, 1, &scissor );
}




void Renderer::insertImageLayoutTransition( ImageResource& imageResource, const ImageResourceUsage& imageResourceUsage, VkCommandBuffer commandBuffer )
{
    {

        VkImageMemoryBarrier2 imageMemoryBarrier{};
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
        imageMemoryBarrier.srcStageMask = imageResource.latestUsageStage;
        imageMemoryBarrier.srcAccessMask = imageResource.latestAccessType;
        imageMemoryBarrier.oldLayout = imageResource.currentLayout;
        imageMemoryBarrier.image = imageResource.image;
        imageMemoryBarrier.dstStageMask = imageResourceUsage.usageStages;
        imageMemoryBarrier.dstAccessMask = imageResourceUsage.usage;
        imageMemoryBarrier.newLayout = imageResourceUsage.layoutForUsage;
        imageMemoryBarrier.subresourceRange.aspectMask = imageResource.aspectFlags; // Color image
        imageMemoryBarrier.subresourceRange.baseMipLevel = imageResource.baseMipLevel; // Single mip level
        imageMemoryBarrier.subresourceRange.levelCount = imageResource.levelCount;
        imageMemoryBarrier.subresourceRange.baseArrayLayer = imageResource.baseArrayLayer; // Single layer
        imageMemoryBarrier.subresourceRange.layerCount = imageResource.layerCount;




        VkDependencyInfo dependencyInfo{};
        dependencyInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
        dependencyInfo.imageMemoryBarrierCount = 1;
        dependencyInfo.pImageMemoryBarriers = &imageMemoryBarrier;

        vkCmdPipelineBarrier2( commandBuffer, &dependencyInfo );

    }
}

//update a DescriptorSlot so that a binding 'points to' a new VkBuffer (or part of a buffer)
void Renderer::updateDescriptorSlot( const VkDevice& logicalDevice, const DescriptorSlot& slot, const VkBuffer& buffer )
{

    VkDescriptorBufferInfo descriptorBufferInfo;
    descriptorBufferInfo.buffer = buffer;
    //"what part of the buffer are we starting from" (even with a dynamic buffer, we're "starting" from 0 with our first element, so I'm just hardcoding this to 0 for now.
    descriptorBufferInfo.offset = 0;
    //if this is a dynamic uniform buffer, then the range should be the size of an 'element' with that buffer.
    //otherwise, it should be the size of the whole buffer.
    descriptorBufferInfo.range = slot.usesDynamicAligment? slot.baseTypeSize: VK_WHOLE_SIZE;

    VkWriteDescriptorSet writeToSetInfoStruct = {};
    writeToSetInfoStruct.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeToSetInfoStruct.pNext = nullptr;
    writeToSetInfoStruct.dstBinding = slot.slotIndexWithinSet;
    CRAYON_ASSERT( slot.owningSet != nullptr );
    writeToSetInfoStruct.dstSet = slot.owningSet->m_descriptorSet; /*m_globalDescriptorSet->m_descriptorSet*/;
    writeToSetInfoStruct.descriptorCount = slot.descriptorCount;
    writeToSetInfoStruct.descriptorType = slot.descriptorType;
    writeToSetInfoStruct.pBufferInfo = &descriptorBufferInfo;

    vkUpdateDescriptorSets( logicalDevice, 1, &writeToSetInfoStruct, 0, nullptr );
}

void Renderer::updateImageResourceState( const ImageResourceUsage& imageResourceUsage, ImageResource& imageResource )
{
    //update the current resource state
    imageResource.latestUsageStage = imageResourceUsage.usageStages;
    imageResource.latestAccessType = imageResourceUsage.usage;
    imageResource.currentLayout = imageResourceUsage.layoutForUsage;
}

void Renderer::updateAttachmentImages( std::vector<const ImageResource*>& imageResources, std::vector<const ImageResourceUsage*>& imageResourceUsages, const VkCommandBuffer& commandBuffer )
{

    CRAYON_ASSERT( imageResources.size() == imageResourceUsages.size() && "You have handed in different-sized arrays of ImageResources and ImageResourceUsages" );

    CRAYON_ASSERT( imageResources.size() > 0 );

    std::vector< VkRenderingAttachmentInfo> colorAttachments;
    bool depthBufferFound = false;
    VkRenderingAttachmentInfo depthAttachment;

    bool renderAreaSet = false;
    VkRect2D renderArea = {};

    for ( size_t i = 0; i < imageResources.size(); i++ )
    {
        if ( !imageResources[i] )
        {
            std::cerr << "An image resource was nullptr";
            abort();
        }
        if ( !imageResourceUsages[i] )
        {
            std::cerr << "An image resource usage was nullptr";
            abort();
        }

        CRAYON_ASSERT( imageResourceUsages[i]->resourceType == ImageResourceType::Attachment);

        //ToDo: renderArea should just be passed in as a separate argument
        if ( !renderAreaSet )
        {
            renderArea = imageResourceUsages[i]->renderArea;
            renderAreaSet = true;
        }

        VkRenderingAttachmentInfo attachment = {};
        attachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
        ///////!!!
        //This is where you plug in the actual image that you're going to render out to in your pass
        attachment.imageView = imageResources[i]->imageView;
        //this describes the layout that your image memory barrier has set the image TO
        attachment.imageLayout = imageResources[i]->currentLayout;//VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        attachment.loadOp = imageResourceUsages[i]->loadOp;
        attachment.storeOp = imageResourceUsages[i]->storeOp;


        //ToDo: should probably take this from the ImageResourceUsage

        if ( !imageResourceUsages[i]->useAsDepthBuffer )
        {
             attachment.clearValue = { {0.0f, 0.0f, 0.0f, 1.0f} };
            colorAttachments.push_back( attachment );
        }

        else
        {
            depthBufferFound = true;
            attachment.clearValue = { 1.0f, 0 };
            depthAttachment=attachment;
        }
    }


    CRAYON_ASSERT( renderAreaSet );

    VkRenderingInfo renderInfo = {};
    renderInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
    renderInfo.renderArea = renderArea;
    renderInfo.layerCount = 1;
    renderInfo.colorAttachmentCount = colorAttachments.size();
    renderInfo.pColorAttachments = colorAttachments.data();
    renderInfo.pDepthAttachment = depthBufferFound? &depthAttachment: nullptr;
    //ToDo: don't hardcode this in: it depends on the pipeline
    renderInfo.pStencilAttachment = nullptr;

    vkCmdBeginRendering( commandBuffer, &renderInfo );

}

void Renderer::resetImageResources()
{
    //When you get rid of m_stagingImageResource, you can pretty much get rid of this... other than to reset access stages and access  types? I'm not even sure where this is called. You may also want to reset the layout to 'undefined' for non-persistent images, but whatever.
    //BECAUSE THIS IS THE FIRST PASS, WE RESET THE IMAGE RESOURCE STATE, includeing latest usage etc.

    getCurrentFrame().preprocessingImage.latestUsageStage = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT;
    getCurrentFrame().preprocessingImage.latestAccessType = VK_ACCESS_2_NONE;
    getCurrentFrame().preprocessingImage.currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    ImageResource& swapchainImageResource = m_swapchainImageResources[getCurrentFrame().currentSwapChainImageIndex_NOTFrameDataIndex];


    swapchainImageResource.latestAccessType = VK_ACCESS_NONE;
    swapchainImageResource.latestUsageStage = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT;
    swapchainImageResource.currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
}

//NB only actually begins a new (dynamic) renderpass if we need to change the attachment image: otherwise is really just about inserting the image layout transitions
void Renderer::beginRenderpass( std::vector<const ImageResourceUsage*>& imageResourceUsages, std::vector< ImageResource*>& imageResources, const VkCommandBuffer& commandBuffer )
{
    CRAYON_ASSERT( imageResourceUsages.size() == imageResources.size() && "BeginRenderpass: non-equal number of ImageResources and ImageResourceUsages handed in");

    std::vector<const ImageResource*> attachmentImageResources;
    std::vector<const ImageResourceUsage*> attachmentImageResourceUsages;

    for ( size_t i = 0; i < imageResources.size(); i++ )
    {
        CRAYON_ASSERT( imageResources[i] && imageResourceUsages[i] );
        insertImageLayoutTransition( *imageResources[i], *imageResourceUsages[i], commandBuffer);
        updateImageResourceState( *imageResourceUsages[i], *imageResources[i]);
        if ( imageResourceUsages[i]->resourceType == ImageResourceType::Attachment )
        {
            attachmentImageResources.push_back( imageResources[i] );
            attachmentImageResourceUsages.push_back( imageResourceUsages[i] );
        }
    }

    if ( attachmentImageResources.size() > 0 )
    {
        updateAttachmentImages( attachmentImageResources, attachmentImageResourceUsages, commandBuffer );
    }
}


void Renderer::beginRenderpass_main()
{
    
    getCurrentFrame().preprocessingImage.currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    ImageResourceUsage stagingImageUsage;
    stagingImageUsage.usageStages = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;// maybe this should just be the fragment stage?
    stagingImageUsage.usage = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
    stagingImageUsage.layoutForUsage = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    stagingImageUsage.resourceType = ImageResourceType::Attachment;
    stagingImageUsage.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    stagingImageUsage.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

    //ToDo: don't hardcode this! Bad idea!
    stagingImageUsage.renderArea = { { 0, 0 }, { m_screenWidth, m_screenHeight } };
    stagingImageUsage.firstPass = true;


    getCurrentFrame().preprocessingDepthBuffer.currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    ImageResourceUsage depthBufferUsage;
    depthBufferUsage.usageStages = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT;
    depthBufferUsage.usage= VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
    depthBufferUsage.layoutForUsage = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    depthBufferUsage.resourceType = ImageResourceType::Attachment;
    depthBufferUsage.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthBufferUsage.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    depthBufferUsage.renderArea = stagingImageUsage.renderArea;
    depthBufferUsage.useAsDepthBuffer = true;

    std::vector<const ImageResourceUsage*> imageResourceUsages;
    std::vector< ImageResource*> imageResources;
    imageResourceUsages.push_back( &stagingImageUsage );
    imageResources.push_back( &getCurrentFrame().preprocessingImage );

    imageResourceUsages.push_back( &depthBufferUsage );
    imageResources.push_back( &getCurrentFrame().preprocessingDepthBuffer );

    beginRenderpass( imageResourceUsages, imageResources, getCurrentFrame().mainCommandBuffer );

}

void Renderer::beginRenderpass_postprocessing()
{
    ImageResourceUsage swapchainImageUsage;
    swapchainImageUsage.usageStages = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
    swapchainImageUsage.usage = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
    swapchainImageUsage.layoutForUsage = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    swapchainImageUsage.resourceType = ImageResourceType::Attachment;
    swapchainImageUsage.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    swapchainImageUsage.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    //ToDo: surely this should be specified by the RESOURCE ITSELF, rather than the usage?
    swapchainImageUsage.renderArea = { { 0, 0 }, { m_screenWidth, m_screenHeight } };
    swapchainImageUsage.firstPass = false;

    ImageResourceUsage stagingImageUsage;
    stagingImageUsage.usageStages = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    stagingImageUsage.usage = VK_ACCESS_2_SHADER_READ_BIT;
    stagingImageUsage.layoutForUsage = VK_IMAGE_LAYOUT_GENERAL;
    stagingImageUsage.resourceType = ImageResourceType::Texture;
    stagingImageUsage.firstPass = false;
    //ToDo: YOU HAVE TO GET RID OF THIS OR IT WILL CAUSE BUGS WHEN YOU WANT TO RENDER OUT TO A LOWER RESOLUTION AND THEN SCALE UP.
    //This needs a rethink: it should be called 'renderAreaOverride' or something, and for now I woundn't bother having it at all, and rather take the image dimensions FROM THE IMAGE ITSELF:
    //PS YOU HAVE TO CHECK THAT THESE DIMENSIONS ARE BEING PROPERLY UPDATED: I would get rid of m_screenWidth and m_screenHeight entirely
    stagingImageUsage.renderArea = { { 0, 0 }, { m_screenWidth, m_screenHeight } };

    
    
    
    FrameData& currentFrameData = getCurrentFrame();

    ImageResource& nextAvailableSwapchainImageResource = m_swapchainImageResources[currentFrameData.currentSwapChainImageIndex_NOTFrameDataIndex];

    VkCommandBuffer& currentCommandBuffer = getCurrentFrame().mainCommandBuffer;

    std::vector<const ImageResourceUsage*> imageResourceUsages;
    std::vector<ImageResource*> imageResources;

    imageResources.push_back( &currentFrameData.preprocessingImage );
    imageResourceUsages.push_back( &stagingImageUsage );

    imageResources.push_back( &nextAvailableSwapchainImageResource );
    imageResourceUsages.push_back( &swapchainImageUsage );

    beginRenderpass( imageResourceUsages, imageResources, currentCommandBuffer );


}



void Renderer::bindDescriptorSuperset(const DescriptorSuperset& superset, const Pipeline& pipeline, const VkCommandBuffer& commandBuffer )
{

    std::vector<VkDescriptorSet> descriptorSets;
    std::vector<uint32_t> offsets;


    for ( const auto& set : superset.m_sets )
    {
        descriptorSets.push_back( set->m_descriptorSet );
        for ( const auto& slot :  set->m_slots | std::ranges::views::values )
        {
            if ( slot -> usesDynamicAligment )
            {
                CRAYON_ASSERT( slot->dynamicAlignment > 0 && "A descriptor slot's dynamic alignment was 0 or less" );
                uint32_t offset = slot-> dynamicAlignment * slot-> currentIndex;
                offsets.push_back( offset );
            }
        }
    }



    vkCmdBindDescriptorSets( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.m_pipelineLayout, 0, descriptorSets.size(), descriptorSets.data(), offsets.size(), offsets.data());
    
}


void Renderer::sumbitCommandBuffer( const VkQueue& graphicsQueue, FrameData& frameData )
{
    //this is the command buffer we'll be submitting
    VkCommandBufferSubmitInfo cmdBufferInfo{};
    cmdBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
    cmdBufferInfo.commandBuffer = frameData.mainCommandBuffer;

    //before executing this command buffer submit call, we need to wait for the image to be available (I mean, the very first thing that we do is to take that image and convert it into a format that's optimized to write to)
    VkSemaphoreSubmitInfo waitSemaphoreInfo{};
    waitSemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    waitSemaphoreInfo.semaphore = frameData.imageAvailableSempahore;
    //...and specifically, the color_attachment stage is the stage that needs to wait
    waitSemaphoreInfo.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;

    //when you finish up with this command buffer, signal the 'imageRenderedToSemaphore'
    VkSemaphoreSubmitInfo signalImageRenderedSemaphoreInfo{};
    signalImageRenderedSemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    signalImageRenderedSemaphoreInfo.semaphore = frameData.imageRenderedToSemaphore;
    //'signal this semaphore once the color_attachment' stage of the pipeline has completed'
    signalImageRenderedSemaphoreInfo.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;

    //our timeline semaphore
    VkSemaphoreSubmitInfo signalCommandBufferFreeSemaphoreInfo{};
    signalCommandBufferFreeSemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    signalCommandBufferFreeSemaphoreInfo.semaphore = frameData.commandBufferFreeSemaphore;
    signalCommandBufferFreeSemaphoreInfo.value = ++frameData.commandBufferFreeTimelineValue;  // When work finishes, increment to the next number
    signalCommandBufferFreeSemaphoreInfo.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;


    VkSemaphoreSubmitInfo signalSemaphores[2] = { signalImageRenderedSemaphoreInfo, signalCommandBufferFreeSemaphoreInfo };


    //tie the command buffer and semaphore info together
    VkSubmitInfo2 submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
    submitInfo.commandBufferInfoCount = 1;
    submitInfo.pCommandBufferInfos = &cmdBufferInfo;
    submitInfo.waitSemaphoreInfoCount = 1;
    submitInfo.pWaitSemaphoreInfos = &waitSemaphoreInfo;
    submitInfo.signalSemaphoreInfoCount = 2;
    submitInfo.pSignalSemaphoreInfos = signalSemaphores;


    //VKQUEUESUBMIT2: actually submit the command buffer
    //Synch:
    //GPU side: needs to wait until image is free and needs to signal when image finished being drawn to
    //CPU side: needs to wait until command buffer free
    //the m_inFlightFence will be signalled once all of the submitted command buffers finish execution
    VkResult submitComBufferResult = vkQueueSubmit2( graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE );
    CRAYON_ASSERT( submitComBufferResult == VK_SUCCESS );
}


//sets up m_hInstance
//vkGuide: VkInstance : WThe Vulkan context, used to access drivers."
//createInstanceInfo<- appInfo, instanceExtensions, (validation) layers
int Renderer::createVulkanInstance( VkInstance& vkInstance )
{
    //-----------------------------------------------
    //set up APP INFO: provide info about the app itself
    //a lot of this stuff doesn't actually do anything, and is just about grouping some info together potentially
    //for debugging etc.
    VkApplicationInfo appInfo = {};

    //vkGuide: When initializing a VkInstance, the name of the application and engine is supplied. 
    //This is so driver vendors can detect the names of AAA games, so they can tweak internal driver logic for them alone. 
    //For normal people, it’s not really important.
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Default";
    appInfo.applicationVersion = VK_MAKE_VERSION( 1, 0, 0 );
    appInfo.pEngineName = "Crayon";
    appInfo.engineVersion = VK_MAKE_VERSION( 1, 0, 0 );
    appInfo.apiVersion = VK_API_VERSION_1_3;

    //--------------------------------------------
    //Now we'll set up the extensions and layers
    //From https://computergraphics.stackexchange.com/questions/8170/what-is-a-vulkan-extension
    //:"Vulkan extensions are simply additional features that Vulkan implementations may provide if they so choose to. 
    //They add new functions, structs, and valid enumerators to the API, and they can change some of the behavior of existing functions."
    //So, my understanding is: the implementation of Vulkan can add certain capabilities, and these are 'extensions',
    //while layers are set up by the Vulkan loader (created by the Vulkan instance) and hook into the drivers to return
    //error info etc.

    std::vector<const char*> instanceExtensions;

    //("KHR" stands for "Khronos" btw)
    instanceExtensions.push_back( VK_KHR_SURFACE_EXTENSION_NAME );
    instanceExtensions.push_back( VK_KHR_WIN32_SURFACE_EXTENSION_NAME );
    instanceExtensions.push_back( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );


    //NB using the Vulkan configurator doesn't mean you can skip setting up the validation layer!
    std::vector<const char*> layers;
    #if VULKAN_DEBUG
        layers.push_back( "VK_LAYER_KHRONOS_validation" );
        std::cout << "Vulkan validation layers enabled" << std::endl;
    #endif // DEBUG_VULKAN

   

    //--------------------------------------------------------------------
    //Create Vulkan Instance
    VkInstanceCreateInfo createInstanceInfo = {};
    createInstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInstanceInfo.pApplicationInfo = &appInfo;
    createInstanceInfo.pNext = nullptr;
    createInstanceInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInstanceInfo.ppEnabledExtensionNames = instanceExtensions.data();
    createInstanceInfo.enabledLayerCount = static_cast<uint32_t>( layers.size());
    createInstanceInfo.ppEnabledLayerNames = layers.data();
    
    VkResult createInstanceResult = vkCreateInstance
    (
        &createInstanceInfo,
        //there's a space here where you can pass in your own special thing governing memory management, but
        //Vulkan does a really good job so we'll leave it!
        nullptr,
        &vkInstance
    );
    CRAYON_ASSERT( createInstanceResult == VK_SUCCESS );

    return 0;
}

void Renderer::createSurface( const HWND& winHandle, const VkInstance& vkInstance, VkSurfaceKHR& surface )
{
    //Now let's set up our SURFACE (a reference to our window, basically)
//GetModuleHandle(NULL) returns an HInstance, and in my understanding its basically a reference to the current
//process
    HINSTANCE hInstance = GetModuleHandle( NULL );
    VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.hinstance = hInstance;
    surfaceInfo.hwnd = winHandle;

    VkResult surfaceCreationResult = vkCreateWin32SurfaceKHR( vkInstance, &surfaceInfo, nullptr, &surface );
    CRAYON_ASSERT( surfaceCreationResult == VK_SUCCESS );
}

//sets up m_commandPool
//Only real choice is whether you're going to set it up so that you can reset individual command buffers, or make it
//so that you can only reset the whole pool. We sometimes want to quickly allocate little command buffers out of the pool to
//deal with sending over data etc. so it makes sense to keep our command buffers resettable
void Renderer::createCommandPool( VkCommandPool& commandPool )
{
    VkCommandPoolCreateInfo comPoolInfo = {};
    comPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    comPoolInfo.pNext = nullptr;
    comPoolInfo.queueFamilyIndex = m_graphicsFamilyIndex;
    //vkTutorial: "VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT: Allow command buffers to be rerecorded individually, 
    //without this flag they all have to be reset together
    //We will be recording a command buffer every frame, so we want to be able to reset and rerecord over it. 
    //Thus, we need to set the VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT flag bit for our command pool."
    comPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    VkResult createComPoolResult = vkCreateCommandPool( m_logDev, &comPoolInfo, nullptr, &commandPool );
    CRAYON_ASSERT( createComPoolResult == VK_SUCCESS );
}

void Renderer::setUpGraphicsQueueCommandPoolsAndBuffers( const VkDevice& logDev, const size_t& graphicsFamilyIndex, VkQueue& graphicsQueue,  std::vector<FrameData>& frameDataStructs )
{
    //Set up command pools (one per frame)
    //(you need a handle to the device queue to se up a command pool)
    vkGetDeviceQueue( logDev, graphicsFamilyIndex, 0, &graphicsQueue );

    VkCommandPoolCreateInfo comPoolInfo = {};
    comPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    comPoolInfo.pNext = nullptr;
    comPoolInfo.queueFamilyIndex = graphicsFamilyIndex;
    comPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    //You'll need a different command buffer for each frame, because you can't start pushing new commands to a pool
    //that's still in use over on the gpu.
    //It's easiest to create a new pool for each frame, too, although I guess you could do it from just the one?
    CRAYON_ASSERT( frameDataStructs.size() == FRAME_OVERLAP );
    for ( uint32_t i = 0; i < FRAME_OVERLAP; i++ )
    {
        VkResult createComPoolResult = vkCreateCommandPool( logDev, &comPoolInfo, nullptr, &frameDataStructs[i].commandPool );
        CRAYON_ASSERT( createComPoolResult == VK_SUCCESS );

        VkCommandBufferAllocateInfo buffAllocInfo = {};
        buffAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        buffAllocInfo.pNext = nullptr;
        buffAllocInfo.commandPool = frameDataStructs[i].commandPool;
        buffAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        buffAllocInfo.commandBufferCount = 1;

        VkResult createComBufferResult = vkAllocateCommandBuffers( logDev, &buffAllocInfo, &frameDataStructs[i].mainCommandBuffer );
        CRAYON_ASSERT( createComBufferResult == VK_SUCCESS );
    }
}


void Renderer::createPipelineLayout( VkPipelineLayout& pipelineLayout, const VkPushConstantRange& pushConstantRange )
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = m_descriptorSuperset.m_sets.size();

    std::vector<VkDescriptorSetLayout> setLayouts;
    for ( const auto& set : m_descriptorSuperset.m_sets )
    {
        setLayouts.push_back( set->m_descriptorSetLayout );
    }

    pipelineLayoutInfo.pSetLayouts = setLayouts.data();
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    VkResult createPipelineLayoutResult = vkCreatePipelineLayout( m_logDev, &pipelineLayoutInfo, nullptr, &pipelineLayout );
    CRAYON_ASSERT( createPipelineLayoutResult == VK_SUCCESS );
}



//vkGuide:"The VkPipeline is a huge object in Vulkan that encompasses the configuration of the entire GPU for the draw. Building them
//can be very expensive, as it will fully convert the shader module into the GPU instructions, and will validate the setup for it."

//The layout has already been created and the shaderes have been compiled into spirv
void Renderer::createPipeline( Pipeline& pipeline, const VkFormat& destinationImageFormat,  float lineThickness)
{
    //We don't use vertex inputs, even in the vertex-shader-based pipelines
    VkPipelineVertexInputStateCreateInfo vInputStateInfo = {};
    vInputStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vInputStateInfo.vertexBindingDescriptionCount = 0;
    vInputStateInfo.pVertexBindingDescriptions = nullptr;
    vInputStateInfo.vertexAttributeDescriptionCount = 0;
    vInputStateInfo.pVertexAttributeDescriptions = nullptr;

    std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfoStructs;

    VkPipelineShaderStageCreateInfo meshShaderStageInfo = {};
    meshShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    meshShaderStageInfo.stage = VK_SHADER_STAGE_MESH_BIT_EXT;
    meshShaderStageInfo.module = pipeline.m_meshShadMod;
    //being able to specify the entrypoint  means that it's possible to combine multiple fragment shaders into a single 
    //shader module and use different entry points to differentiate between their behaviors... but that's way beyond me
    meshShaderStageInfo.pName = "main";
    shaderStageCreateInfoStructs.push_back(meshShaderStageInfo);

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = pipeline.m_fragShadMod;
    fragShaderStageInfo.pName = "main";
    shaderStageCreateInfoStructs.push_back(fragShaderStageInfo);


    //--------------------------------------------
    //set up the FIXED FUNCTION STATES:a lot of this is about rasterization
    //--------------------------------------------
    
    //we'll do the viewport/scissor side of things later: you can make it dynamic, so it isn't baked into the pipeline
    std::vector<VkDynamicState> dynamicStates =
    {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
    };

    VkPipelineDynamicStateCreateInfo dynamicState = {};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    //you now combine the viewport and the scissor into a 'vieport state'
    VkPipelineViewportStateCreateInfo viewportStateInfo = {};
    viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateInfo.viewportCount = 1;
    viewportStateInfo.pViewports = nullptr;
    viewportStateInfo.scissorCount = 1;
    viewportStateInfo.pScissors = nullptr;

    //Now we'll set up the rasterizerStateInfo
    VkPipelineRasterizationStateCreateInfo rasterizerStateInfo = {};
    rasterizerStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    //If depthClampEnable is set to VK_TRUE, then fragments that are beyond the near 
    //and far planes are clamped to them as opposed to discarding them.
    rasterizerStateInfo.depthClampEnable = VK_FALSE;
    //rasterizerDiscard is set to true when you don't want to send things to the rasterizer at all
    rasterizerStateInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizerStateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizerStateInfo.lineWidth = lineThickness;
    //VK_CULL_MODE_BACK_BIT specifies that back-facing triangles are discarded
    rasterizerStateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizerStateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizerStateInfo.depthBiasEnable = VK_FALSE;
    rasterizerStateInfo.depthBiasConstantFactor = 0.0f;
    rasterizerStateInfo.depthBiasClamp = 0.0f;
    rasterizerStateInfo.depthBiasSlopeFactor = 0.0f;

    //multisampling is used for antialiasing, which we're not worried about right now
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;
    multisampling.pSampleMask = nullptr;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable = VK_FALSE;

    //Now we need to say how we want colour blending to happen
    //I don't understand color blending: at the moment I've just set up the shaders to discard any pixel that isn't
    //100% opaque. I did try to get transparency working but I think I'll leave it for the future.
    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    //don't mask out anything
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    //don't blend: just use the new colour coming in
    colorBlendAttachment.blendEnable = VK_TRUE;
    //seeing as we're not blending, don't worry about any of the stuff below
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; 
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; 
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    //this seems to just be about grouping a bunch of color attachment states together, but we don't need to do that  so it's
    //pretty pointless
    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;


    VkPipelineRenderingCreateInfo renderingInfo = {};
    renderingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
    renderingInfo.colorAttachmentCount = 1;
    renderingInfo.pColorAttachmentFormats = &destinationImageFormat;
    renderingInfo.depthAttachmentFormat = pipeline.m_usesDepthBuffer ? DEPTH_BUFFER_DEFAULT_FORMAT : VK_FORMAT_UNDEFINED;// Your swapchain format



    VkGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = shaderStageCreateInfoStructs.size();
    pipelineInfo.pStages = shaderStageCreateInfoStructs.data();

    if ( pipeline.m_shaderType == ShaderType::VERTEX )
    {
        pipelineInfo.pVertexInputState = &vInputStateInfo;
        pipelineInfo.pInputAssemblyState = &pipeline.m_inputAssemblyInfo;
    }
    else if (pipeline.m_shaderType==ShaderType::MESH )
    {
        pipelineInfo.pVertexInputState = nullptr;
        pipelineInfo.pInputAssemblyState = nullptr;
    }
    pipelineInfo.pViewportState = &viewportStateInfo;
    pipelineInfo.pRasterizationState = &rasterizerStateInfo;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = pipeline.m_usesDepthBuffer ? &DEPTH_STENCIL_DEFAULT_SETTINGS : nullptr;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = pipeline.m_pipelineLayout;
    pipelineInfo.renderPass = VK_NULL_HANDLE;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = -1;
    pipelineInfo.pNext = &renderingInfo;

    VkResult createPipelineResult = vkCreateGraphicsPipelines( m_logDev, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline.m_pipeline );

    CRAYON_ASSERT( createPipelineResult == VK_SUCCESS );
}
//end of createPipeline()


//set up m_swapchain, m_swapchainImages and m_swapchainImageViews
//While the swapchain itself, the swapchain images, and the swapchain image views are all obviously tied up with one another, we keep separate references to the different parts. NB you don't need to worry about allocating memory to the images or destroying them because they are directly 'owned' by the swapchain, but you do need to remember to clean up the swapchain image views yourself.
void Renderer::createSwapChain( HWND winHandle)
{
    //now we need to see if the graphics queue family we found on our gpu is able to output to our surface
    VkBool32 supportsSurface = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR( m_physDev, m_graphicsFamilyIndex, m_surface, &supportsSurface );

    CRAYON_ASSERT( supportsSurface == VK_TRUE );


    //Now we need to find out what formats our physical device supports
    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR( m_physDev, m_surface, &formatCount, nullptr );
    CRAYON_ASSERT( formatCount > 0 );
    std::vector<VkSurfaceFormatKHR>supportedFormats( formatCount );
    vkGetPhysicalDeviceSurfaceFormatsKHR( m_physDev, m_surface, &formatCount, supportedFormats.data() );

	bool desiredFormatFound = false;

    for ( const auto& format : supportedFormats )
    {
		if ( format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
        {
			m_surfaceFormat = format;
            desiredFormatFound = true;
			break;
		}
    }

    //ToDo: we should probably add some code so that if we can't find a format that supports sRGB images, we can do the gamma
    //correction manually in the fragment shader or whatever. But it seems pretty unlikely? Like... what GPU doesn't support
    //SRGB?
	CRAYON_ASSERT( desiredFormatFound );


    m_surfaceFormat.format = VK_FORMAT_B8G8R8A8_SRGB;
	m_surfaceFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    
    //now we need to ask what the surface's capabilities are, so that we can plug them into the swapchain info
    //later
    VkSurfaceCapabilitiesKHR surfaceCapabilities;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR( m_physDev, m_surface, &surfaceCapabilities );

    //that doesn't tell us all the present modes that a surface supports, so we have to do that separately
    uint32_t presentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR( m_physDev, m_surface, &presentModeCount, nullptr );

    CRAYON_ASSERT( presentModeCount > 0 );

    std::vector<VkPresentModeKHR>presentModes( presentModeCount );
    vkGetPhysicalDeviceSurfacePresentModesKHR( m_physDev, m_surface, &presentModeCount, presentModes.data() );

    //get window width and height
    RECT windowRect{};
    GetClientRect( winHandle, &windowRect );

    m_screenWidth = windowRect.right - windowRect.left;
    m_screenHeight = windowRect.bottom - windowRect.top;

    //swapchain creation code follows Tu Wien University Youtube tutorial series:
    //Youtube.com. 2022. Swap Chain | "Presentation Modes and Swap Chain Setup in Vulkan" | Vulkan Lecture Series, Episode 2.[online] 
    //Available at : < https ://www.youtube.com/watch?v=nSzQcyQTtRY&list=PLmIqTlJ6KsE0UsR2E_84-twxX6G7ynZNq&index=6> 
    //[Accessed 11 April 2022].
    m_swapchainInfo = {};
    m_swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    m_swapchainInfo.pNext = nullptr;
    m_swapchainInfo.surface = m_surface;
    m_swapchainInfo.flags = 0;
    m_swapchainInfo.minImageCount = 4;
    //TO DO: does this need to match the format we used earlier when we were creating the surface? Because I think there
    //it was BGRA...
    //Answer: Yes!
    m_swapchainInfo.imageFormat = m_surfaceFormat.format;
    m_swapchainInfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    m_swapchainInfo.imageExtent = VkExtent2D{ m_screenWidth, m_screenHeight };
    m_swapchainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    m_swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    //I think this is only for doing things in stereoscopic 3d
    m_swapchainInfo.imageArrayLayers = 1;
    //ToDo: put this into a SwapchainInfo struct that you can reuse around the place, that stores things like the number of layer etc. (it'll basically store the same image that this transient VkSwapchainInfo struct does)
    //You could also store the width and height in here, in case they ever differed from the window width and height (though maybe that shouldn't ever happen... who knows?)
    //we need 'VK_IMAGE_USAGE_TRANSFER_DST_BIT' so that you can also copy into the swapchain image instead of having to render to it directly
    m_swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT| VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    m_swapchainInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    m_swapchainInfo.oldSwapchain = VK_NULL_HANDLE;
    m_swapchainInfo.clipped = VK_TRUE;
    //we don't want to share images between queues
    m_swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    //these 2 only used when you're sharing images between queues
    m_swapchainInfo.queueFamilyIndexCount = 0;
    m_swapchainInfo.pQueueFamilyIndices = nullptr;

    VkResult createSwapchainResult = vkCreateSwapchainKHR( m_logDev, &m_swapchainInfo, nullptr, &m_swapchain );

    //while we ask for a minImageCount when we create the swapchain, we now need to find out how many images
    //we actually got, and store references to them. Then, we can create the imageViews for those images.
    //renderpassbegininfo<- framebuffer <- imageView <- image
    {
        uint32_t imageCount = 0;

        vkGetSwapchainImagesKHR( m_logDev, m_swapchain, &imageCount, nullptr );

        CRAYON_ASSERT( imageCount > 0 );

        m_swapchainImageResources.resize( imageCount );

        {
            std::vector<VkImage> swapChainImages;
            for ( const auto& imageResource : m_swapchainImageResources )
            {
                swapChainImages.push_back( imageResource.image );
            }


            VkResult getImagesResult = vkGetSwapchainImagesKHR( m_logDev, m_swapchain, &imageCount,     swapChainImages.data() );
            CRAYON_ASSERT( getImagesResult == VK_SUCCESS );

            CRAYON_ASSERT( swapChainImages.size() == m_swapchainImageResources.size() );
            for ( size_t i = 0; i < swapChainImages.size(); i++ )
            {
                m_swapchainImageResources[i].image = swapChainImages[i];
                m_swapchainImageResources[i].imageFormat = getSwapchainImageFormat();
            }
        }

        for ( auto& swapchainImageResource : m_swapchainImageResources )
        {
            swapchainImageResource.imageView = createImageView( swapchainImageResource.image, m_surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT );
        }

    }
}
//end of createSwapChain()

//sets up m_physDevProperties and m_graphicsFamilyIndex
//you don't CREATE a physical device: you just choose one, and then you go and get the index of the queue family that
//can handle graphics
void Renderer::initPhysicalDevice()
{
    //get number of physical devices
    uint32_t devCount = 0;
    vkEnumeratePhysicalDevices( m_vkInstance, &devCount, nullptr );
    CRAYON_ASSERT( devCount > 0 );
    std::vector<VkPhysicalDevice> devices( devCount );
    vkEnumeratePhysicalDevices( m_vkInstance, &devCount, devices.data() );

    //If we find a standalone gpu, we'll use that. Otherwise, we use the first gpu we find.
    uint32_t chosenGPUIndex = 0;

    for ( size_t i = 0; i < devices.size(); i++ )
    {
        vkGetPhysicalDeviceProperties( devices[i], &m_physDevProperties );

        if ( m_physDevProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU )
        {
            chosenGPUIndex = static_cast<uint32_t>(i);
        }
    }

    m_physDev = devices[chosenGPUIndex];

    //now we'll look to see what queue family on the index supports graphics operations
    //first off, let's see how many queue families there are on the gpu
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties( devices[chosenGPUIndex], &queueFamilyCount, nullptr );
    //now we'll store the properties - the capabilites - of each of those queue families in a vector
    std::vector<VkQueueFamilyProperties> queueFamilies( queueFamilyCount );
    vkGetPhysicalDeviceQueueFamilyProperties( devices[chosenGPUIndex], &queueFamilyCount, queueFamilies.data() );

    //Now we'll go through, and as soon as we find a queue family that supports graphics operations, we'll remember what the index of that
    //queue family was (as in, literally just if it was the 1st queue family, the 2nd etc.) and we'll move on
    VkBool32 canDoGraphics = VK_FALSE;
    for ( size_t i = 0; i < queueFamilies.size(); i++ )
    {
        //"if we can actually create a queue out of that queue family, and if the graphics bit is set to true
        //for that queueFamily (I feel like "queueFlags" should be called "queueFamilyFlags" but whatever)..".
        if ( (queueFamilies[i].queueCount > 0) && (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) )
        {
            canDoGraphics = true;
            m_graphicsFamilyIndex = static_cast<uint32_t> (i);
            break;
        }
    }
    CRAYON_ASSERT( canDoGraphics );
}

//sets up m_logDev
void Renderer::createLogicalDevice()
{
    //We are going to create a VkDeviceCreateInfo struct.
    //It has 2 important fields.

    //1)The first is pEnabledFeatures, which is a pointer to a VkPhsycialDeviceFeatures struct.
    //Physical device features are hardware capabilities: like, 'can this card handle mesh shaders' or whatever. They're not a Vulkan extension in themselves: our GPU might be able to handle mesh shaders but our VulkanSDK might not have the extension for them.

    //This field is a real pain:
    //The problem is, the standard VkPhysicalDeviceFeatures struct doesn't know about several of the newer features. So we create a VkPhysicalDeviceFeatures2 struct. This is basically just a wrapper around a regular VkPhsyicalDeviceFeatures struct, into which we plug 'anistropy' or whatever core, standard device features we want to enable.
    //But it also has a 'pNext' field, and with this we can create a chain of specific, non-standard device features, like a VkPhysicalDeviceMeshShaderFeaturesEXT struct, which can then link to a VkPhysicalDeviceVulkan13Features struct etc. etc.

    //So to recap: VkDeviceCreateInfo has a slot you can plug a VkPhysicalDeviceFeatures struct into.
    //But that's very inflexible. So instead we leave that blank, and we chain the VkDeviceCreateInfo to a VkDeviceCreateInfo2 struct instead. This contains all the regular VkPhsyicalDeviceFeatures stuff, but it also itself has a pNext field that you can link to a new hardware feature struct, which can then link to another hardware feature struct etc.

    //I think the most confusing part of this is: why didn't they just give the standard VkPhysicalDeviceFEatures struct a pNext field so that you could just do the chaining that way? It feels very weird to leave the pEnabledFeatures field blank: there's nothing that really tells you that pNext is going to be where you plug in non-standard device feature stuff instead.

    //Maybe it was just an oversight.

    //2) ppDeviceExtensionNames

    //Just an array of Vulkan extension c-string names.
    //An extension is something like the swapchain extension: it's not a hardware feature (all GPUs can give you a swapchain), but because swapchains are hardware-specific they're not part of the core Vulkan API so you have to request the extension.

////////////////////////////////////////////////////
    //Hardware features vs. Vulkan extensions
    //So, some things like the khr swapchain are just an extension, and other things like enabling mesh shading involve both activating the hardware mesh shading capabilities and also enabling the related Vulkan extensions.



    //-----------------------------------------
    //SET UP EXTENSIONS
    // 
    // First, get a vector of VkExtensionProperties. Each of these contains a string specifying the extension name.
    // 
    //This is a common pattern in Vulkan with enumeration functions: you call the first time with a nullptr destination and just get a count back, and then you call again to actually get the data.
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties( m_physDev, nullptr, &extensionCount, nullptr );
    std::vector<VkExtensionProperties> availableExtensions( extensionCount );
    vkEnumerateDeviceExtensionProperties( m_physDev, nullptr, &extensionCount, availableExtensions.data() );
    
    
    std::vector<const char*> deviceExtensionNames;
    deviceExtensionNames.push_back( VK_KHR_SWAPCHAIN_EXTENSION_NAME );
    deviceExtensionNames.push_back( "VK_EXT_mesh_shader" );
    deviceExtensionNames.push_back( "VK_KHR_dynamic_rendering" );
    deviceExtensionNames.push_back( "VK_KHR_synchronization2" );
    deviceExtensionNames.push_back( VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME );
   
    for ( const auto& desiredExtensionName : deviceExtensionNames )
    {
        bool extensionSupported = false;
        for ( const auto& availableExtension : availableExtensions )
        {
            //strcmp is how you compare to C-style strings. If it returns 0, there is no difference.
            if ( strcmp( availableExtension.extensionName, desiredExtensionName ) == 0)            
            {
                extensionSupported = true;
                break;
            }
        }

        CRAYON_ASSERT( extensionSupported == true );
    }









    //SET UP DEVICE FEATURES
    // 
    //Device features are where you check what your hardware can actually do: like, does it support raytracing etc.

   
        //You need to set up multiple (identical) device feature chains, so to avoid inconsitency I've just merged them into a single struct
        struct DeviceFeatureChain
        {
            //If you want to enable more features, just do it here
            VkPhysicalDeviceFeatures2 chainStart{}; // start of the chain
            VkPhysicalDeviceDescriptorIndexingFeaturesEXT indexingFeatures{};
            VkPhysicalDeviceMeshShaderFeaturesEXT meshShaderFeatures{};
            VkPhysicalDeviceVulkan13Features features13{};
            VkPhysicalDeviceTimelineSemaphoreFeatures timelineFeatures{};

        public:
            DeviceFeatureChain()
            {
                chainStart = {};
                chainStart.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
                chainStart.features.samplerAnisotropy = VK_TRUE;
                chainStart.features.fragmentStoresAndAtomics = VK_TRUE;
            
                indexingFeatures={};
                indexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;
                indexingFeatures.runtimeDescriptorArray = VK_TRUE;
                indexingFeatures.descriptorBindingVariableDescriptorCount = VK_TRUE;
                indexingFeatures.descriptorBindingPartiallyBound = VK_TRUE;
                chainStart.pNext = &indexingFeatures;

                meshShaderFeatures = {};
                meshShaderFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;
                meshShaderFeatures.meshShader = VK_TRUE;
                meshShaderFeatures.taskShader = VK_TRUE;
                indexingFeatures.pNext = &meshShaderFeatures;

                timelineFeatures = {};
                timelineFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
                timelineFeatures.timelineSemaphore = VK_TRUE;
                meshShaderFeatures.pNext = &timelineFeatures;


                features13 = {};
                features13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
                //Maintenance4 (maintenance4 in VkPhysicalDeviceVulkan13Features) is a collection of small quality-of-life improvements to Vulkan. Some key things it enables:
               /*   . Allows you to destroy a pipeline or pipeline layout that's still in use by a command buffer that hasn't finished executing
                    . Lets you mix push constants and push descriptor sets in one descriptor set layout
                    . Improves image layout transitions - you no longer need to split barriers that change image formats or aspects
                    . Enables you to access descriptor set memory consistently with non - uniform indexing
                    . Lets you share presentable images between Windows and Linux / X11*/
                features13.maintenance4 = VK_TRUE;
                features13.dynamicRendering = VK_TRUE;
                timelineFeatures.pNext = &features13;
                features13.synchronization2 = VK_TRUE;
            }


        };


        {
            DeviceFeatureChain availableFeatureChain{};

            vkGetPhysicalDeviceFeatures2( m_physDev, &availableFeatureChain.chainStart );

            CRAYON_ASSERT( availableFeatureChain.chainStart.features.samplerAnisotropy );
            CRAYON_ASSERT( availableFeatureChain.chainStart.features.fragmentStoresAndAtomics );
            CRAYON_ASSERT( availableFeatureChain.indexingFeatures.descriptorBindingPartiallyBound&& availableFeatureChain.indexingFeatures.runtimeDescriptorArray );
            CRAYON_ASSERT( availableFeatureChain.indexingFeatures.descriptorBindingVariableDescriptorCount == VK_TRUE );
            CRAYON_ASSERT( availableFeatureChain.meshShaderFeatures.meshShader );
            CRAYON_ASSERT( availableFeatureChain.meshShaderFeatures.taskShader );
            CRAYON_ASSERT( availableFeatureChain.features13.maintenance4 );
            CRAYON_ASSERT( availableFeatureChain.features13.dynamicRendering );
            CRAYON_ASSERT( availableFeatureChain.features13.synchronization2 );
            CRAYON_ASSERT( availableFeatureChain.timelineFeatures.timelineSemaphore );

        }

   

    DeviceFeatureChain desiredFeatures{};


    VkDeviceQueueCreateInfo queueInfo = {};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = m_graphicsFamilyIndex;
    queueInfo.queueCount = 1;
    //(you have to have a "queuePriority", even if you only have 1 queue)
    float queuePritority = 1.f;
    queueInfo.pQueuePriorities = &queuePritority;

    VkDeviceCreateInfo logDevInfo = {};
    logDevInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    logDevInfo.pNext = &desiredFeatures.chainStart;
    //remember, queueInfo thinks it has an array of pQueuePriorities, and we now need to say how big that array is
    logDevInfo.queueCreateInfoCount = 1; 
    logDevInfo.pQueueCreateInfos = &queueInfo;
    logDevInfo.pEnabledFeatures = nullptr;
    logDevInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensionNames.size());
    logDevInfo.ppEnabledExtensionNames = deviceExtensionNames.data();
    logDevInfo.enabledLayerCount = 0;

    VkResult createLogDevResult = vkCreateDevice( m_physDev, &logDevInfo, nullptr, &m_logDev );
    CRAYON_ASSERT( createLogDevResult == VK_SUCCESS );
}



//sets up an index buffer
void Renderer::setUpIndexBuffer( AllocatedBuffer& allocatedBuffer, std::vector<uint16_t>& indices)
{
    VkDeviceSize indexBufferSize = sizeof( indices[0]) * indices.size();

    //create a temporary staging buffer
    AllocatedBuffer indexStagingBuffer;
    createVmaBuffer( indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, indexStagingBuffer, VMA_MEMORY_USAGE_CPU_TO_GPU );
    mapMemory( indexStagingBuffer, indices.data(), indexBufferSize);

    //now we'll create the actual, high-performance index buffer
    createVmaBuffer( indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, allocatedBuffer, VMA_MEMORY_USAGE_GPU_ONLY );
    m_allocatedBuffers.push_back( allocatedBuffer );

    //now we copy the data accross, and destroy the staging buffer
    copyBuffer( indexStagingBuffer.buffer, allocatedBuffer.buffer, indexBufferSize );
    vmaDestroyBuffer( m_vmaAllocator, indexStagingBuffer.buffer, indexStagingBuffer.allocation );
}

void Renderer::setScreenExtent( const uint32_t width, const uint32_t height )
{
    m_screenWidth = width;
    m_screenHeight = height;
}



//load in the SPIRV shader code from file, and put it into a vector of chars.
//then put those characters into a VkShaderModuleCreateInfo struct (reinterpreting them as uint32_ts) and create a shader module
//out of them
void Renderer::loadShaderModule( const char* filePath, VkShaderModule* pOutShaderModule )
{
    //"ate"="at the end"
    //"binary": don't do anything weird to the data to interpret it as characters
    std::ifstream shaderFile( filePath, std::ios::ate | std::ios::binary );

    CRAYON_ASSERT( shaderFile.is_open() );

    //tellg(): returns the position of the current character in the input stream. Because we've placed
    //our cursor at the end of the file, we can work out directly from this how big the file is
    int fileSize = shaderFile.tellg(); 
    std::vector<char>shaderByteCode( fileSize );
    //Sets the position of the next character to be extracted from the input stream.
    shaderFile.seekg( 0 );
    shaderFile.read( shaderByteCode.data(), fileSize );
    shaderFile.close();

    //----------------------------
    //Now we need to put the shaders into shader modules.
    //Shader modules are just a thin wrapper around the shader bytecode, holding info re. how big the bytecode is etc.
    VkShaderModuleCreateInfo shaderModuleInfo = {};
    shaderModuleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleInfo.codeSize = shaderByteCode.size();
    shaderModuleInfo.pCode = reinterpret_cast<const uint32_t*>(shaderByteCode.data());

    VkResult createVShadModResult = vkCreateShaderModule( m_logDev, &shaderModuleInfo, nullptr, pOutShaderModule );
    CRAYON_ASSERT( createVShadModResult == VK_SUCCESS );
}



void Renderer::cleanUp()
{
    vkDeviceWaitIdle( m_logDev );

    for ( auto &frameDataStruct: m_frameDataStructs )
    {
        vkDestroyCommandPool( m_logDev, frameDataStruct.commandPool, nullptr );
        frameDataStruct.commandPool = VK_NULL_HANDLE;

        vkDestroySemaphore( m_logDev, frameDataStruct.imageAvailableSempahore, nullptr );
        frameDataStruct.imageAvailableSempahore = VK_NULL_HANDLE;

        vkDestroySemaphore( m_logDev, frameDataStruct.imageRenderedToSemaphore, nullptr );
        frameDataStruct.imageAvailableSempahore = VK_NULL_HANDLE;

        vkDestroySemaphore( m_logDev, frameDataStruct.commandBufferFreeSemaphore, nullptr );
        frameDataStruct.commandBufferFreeSemaphore = VK_NULL_HANDLE;
    }

    for ( Pipeline* pipeline : m_pipelines )
    {
        if ( pipeline != nullptr )
        {
            pipeline->cleanup();
        }
    }

    vkDestroySampler( m_logDev, m_textureSampler, nullptr );

    //ToDo: we obviously need to have these automatically added to an array that clears them up
    /*vkDestroyDescriptorSetLayout( m_logDev, m_globalDescriptorSet->m_descriptorSetLayout, nullptr);
    vkDestroyDescriptorSetLayout( m_logDev,m_stagingImagesDescriptorSet->m_descriptorSetLayout, nullptr );*/

    for ( auto& set : m_descriptorSuperset.m_sets )
    {
        vkDestroyDescriptorSetLayout(m_logDev, set->m_descriptorSetLayout, nullptr );
    }

    if ( m_descriptorPool != VK_NULL_HANDLE )
    {
        vkDestroyDescriptorPool( m_logDev, m_descriptorPool, nullptr );
    }


    for ( size_t i = 0; i < m_allocatedBuffers.size(); i++ )
    {
        vmaDestroyBuffer( m_vmaAllocator, m_allocatedBuffers[i].buffer, m_allocatedBuffers[i].allocation );
    }


    for ( size_t i = 0; i < m_textureHandles.size(); i++ )
    {
        vkDestroyImageView( m_logDev, m_textureHandles[i].imageView, nullptr );
        vmaDestroyImage( m_vmaAllocator, m_textureHandles[i].image, 
            m_textureHandles[i].imageAllocation );
    }

    cleanUpPreprocessingImagesAndTheirDepthBuffers();



    //clean up swapchain image views
    for ( auto& swapchainImageResource: m_swapchainImageResources )
    {
        CRAYON_ASSERT( swapchainImageResource.imageView != VK_NULL_HANDLE );
        vkDestroyImageView( m_logDev, swapchainImageResource.imageView, nullptr );
        swapchainImageResource.imageView = VK_NULL_HANDLE;
    }
    

    //CLEANUP PIPELINES







    //clear up swapchain stuff
    //NB the swapchain images are automatically destroyed with the swapchain, though we still need to manually destroy the image VIEWS for the swapchain
    vkDestroySwapchainKHR( m_logDev, m_swapchain, nullptr );


    vkDestroyDevice( m_logDev, nullptr );

    vkDestroySurfaceKHR( m_vkInstance, m_surface, nullptr );
    {
        //destroy the vulkan debug messenger
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            m_vkInstance, "vkDestroyDebugUtilsMessengerEXT" );

        CRAYON_ASSERT( func != nullptr );

        func( m_vkInstance, m_debugMessenger, nullptr );

    }

    vkDestroyInstance
    (
        m_vkInstance,
        //if you're doing manual memory allocation, you can pass in a custom deallocator here
        nullptr 
    );
}


//resets command buffer
//begins command buffer
//starts render pass

//To do: maybe rename this to 'begin pass', because that's what you're really doing
void Renderer::startDrawFrame()
{
    ////////////////////////////////////////////
//get the index of the next available swapchain image
    {
        PROFILE_SCOPE( WaitForCommandBufferFree )

        //ToDo: move this out of this function plz
        //updateCameraPosition();


        //wait for the command buffer to be free
        VkSemaphoreWaitInfo commandBufferSemaphoreWaitInfo{};
        commandBufferSemaphoreWaitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
        commandBufferSemaphoreWaitInfo.semaphoreCount = 1;
        commandBufferSemaphoreWaitInfo.pSemaphores = &getCurrentFrame().commandBufferFreeSemaphore;
        commandBufferSemaphoreWaitInfo.pValues = &getCurrentFrame().commandBufferFreeTimelineValue;
        vkWaitSemaphores( m_logDev, &commandBufferSemaphoreWaitInfo, UINT64_MAX );
    }   //END PROFILE SCOPE


        //when we hand the imageAvailableSemaphore in here, that's saying that the imageAvailableSempahore will be signaled when
        //that image is actually available (vkAcquireNextImage() just gives you the next image that WILL BE available)
    VkResult acquireImageResult = vkAcquireNextImageKHR( m_logDev, m_swapchain, UINT64_MAX, getCurrentFrame().imageAvailableSempahore, VK_NULL_HANDLE, &getCurrentFrame().currentSwapChainImageIndex_NOTFrameDataIndex ); CRAYON_ASSERT( acquireImageResult == VK_SUCCESS );




    /////////////////////////////////////////////////
    //PREP the command buffer to be written to
    vkResetCommandBuffer( getCurrentFrame().mainCommandBuffer, 0 );


    //nothing renderpass-specific here :) Just setting things like 'one time submit' etc.
    // ToDo: although, weirdly, you seem to set up, uh, scissor information? How on earth can that be shared across all the renderpasses? Moreover, why do we then have to set the scissor for reach pass? Very weird.
    setUpCommandBufferWithDesiredSettings( getCurrentFrame().mainCommandBuffer, m_swapchainInfo.imageExtent, m_screenWidth, m_screenHeight );

    resetImageResources();

}

//


void Renderer::endDrawFrame()
{

    ImageResourceUsage swapchainImageResourceUsage;
    swapchainImageResourceUsage.firstPass = false;
    swapchainImageResourceUsage.layoutForUsage = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    //ToDo: get rid of this! Rename it renderAreaOverride etc. and switch it off by default, and instead use the dimensions stored within the imageresource itself
    //swapchainImageResourceUsage.renderArea
    swapchainImageResourceUsage.usageStages = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT;
    swapchainImageResourceUsage.usage = VK_ACCESS_2_NONE;//ToDo: check that this is right: I think I might have gotten turned around here. It shouldn't matter because nothing is actually going to wait for this, but still, it doesn't seem correct.

    swapchainImageResourceUsage.renderArea={ { 0, 0 }, { m_screenWidth, m_screenHeight } };

    //ToDo: We're not rendering out to the swapchain at this point so in our current terminology it's a 'texture', but whether that quite fits I'm not sure. Perhaps a simple boolean 'useAsAttachment' would be better here, I don't know.
    swapchainImageResourceUsage.resourceType = ImageResourceType::Texture;

    std::vector<ImageResource*> imageResources;
    std::vector<const ImageResourceUsage*> imageResourceUsages;

    imageResources.push_back( &m_swapchainImageResources[getCurrentFrame().currentSwapChainImageIndex_NOTFrameDataIndex] );

    imageResourceUsages.push_back( &swapchainImageResourceUsage );

    beginRenderpass( imageResourceUsages, imageResources,  getCurrentFrame().mainCommandBuffer );



    VkResult endComBufferResult = vkEndCommandBuffer( getCurrentFrame().mainCommandBuffer );
    CRAYON_ASSERT( endComBufferResult == VK_SUCCESS );

    sumbitCommandBuffer( m_graphicsQueue, getCurrentFrame() );


    //GPU: needs to wait until image finished being draw to
    //CPU: all good
    //now we need to swap the buffers
    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    //signal sempahores: the current frame's "imageRendererdToSempahore"
    presentInfo.pWaitSemaphores = &getCurrentFrame().imageRenderedToSemaphore;
    VkSwapchainKHR swapChains[] = { m_swapchain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &getCurrentFrame().currentSwapChainImageIndex_NOTFrameDataIndex;
    presentInfo.pResults = nullptr;
    vkQueuePresentKHR( m_graphicsQueue, &presentInfo );

    m_currentFrameNumber++;
}





void Renderer::endRenderPass()
{
    vkCmdEndRendering( getCurrentFrame().mainCommandBuffer );
}



VkFormat Renderer::getSwapchainImageFormat()
{
    return m_surfaceFormat.format;
}

void Renderer::drawGameSprites( std::vector<Sprite>& spriteVector )
{
    draw<Sprite>( m_spritePipeline, spriteVector );
}



void Renderer::drawUISprites( std::vector<Sprite>& spriteVector )
{
    draw<Sprite>( m_uiSpritePipeline, spriteVector );
}

void Renderer::drawSolidShapes( std::vector<Rect>& rectVector )
{
    draw<Rect>( m_solidShapePipeline, rectVector );
}

void Renderer::drawCircles( std::vector<Rect>& rectVector )
{
    draw<Rect>( m_circlePipeline, rectVector );
}




//NB!!! It's called a "VkDescriptorPoolSize" not because it describes the size of an actual, complete
//descriptor pool, but because it describes how much of pool memory something needs: we'll put those
//"descriptor pool sizes" together at the end to find out what the total size of our descriptor pool needs to be.
void Renderer::setUpDescriptorPool(const VkDevice& logDev, const DescriptorSuperset& superset, VkDescriptorPool& descriptorPool)
{

    std::vector<VkDescriptorPoolSize> descriptorPoolSizes;


    for (const auto& set: superset.m_sets )
    {
        ///////////////////////////////////////////////////////////
       /////////////////CREATE POOL
       ///////////////////////////////////////////////////////////


        //NB It's fine to have just one descriptor pointing to our dynamic camera buffer, even though we have multiple frames in flight: when we use vkCmdBindDescriptorSets when drawing to get at a specific slot in the camera buffer,  the descriptor itself is never modified - it's more like a "handle" or "view" into the buffer. When you bind with different offsets in different command buffers, you're just telling each command buffer "when you use this descriptor, offset it by this much."
        //uniform object buffer info

        for ( const auto& slot: std::views::values( set->m_slots))
        {
            VkDescriptorPoolSize size;
            size.type = slot->descriptorType;
            size.descriptorCount = slot->descriptorCount;
            descriptorPoolSizes.push_back( size );
        }

    }
    //now we can create the pool itself.
    VkDescriptorPoolCreateInfo descriptorPoolInfo = {};
    descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(descriptorPoolSizes.size());
    descriptorPoolInfo.pPoolSizes = descriptorPoolSizes.data();
    descriptorPoolInfo.maxSets = superset.m_sets.size();

    VkResult createDescriptorPoolResult = vkCreateDescriptorPool( logDev, &descriptorPoolInfo, nullptr, &descriptorPool );
    CRAYON_ASSERT( createDescriptorPoolResult == VK_SUCCESS );

}

// vkTutorial:  "The descriptor LAYOUT specifies the TYPES of RESOURCES that are going to be accessed by the pipeline,
    // just like a render pass specifies the TYPES of ATTACHMENTS (images) that will be accessed.
    // A descriptor SET specifies the actual buffer or image resources that will be bound to the descriptors, just like a
    // framebuffer specifies the actual image views to bind to render pass attachments".

void Renderer::setUpDescriptorSetLayout( const VkDevice& logDev,  DescriptorSet& descriptorSet)
{
    ///////////////////////////////////////////////////////////
  /////////////////CREATE DESCRIPTOR SET LAYOUT
  ///////////////////////////////////////////////////////////
    //NB The layout is a handle, and we need to clean it up at the end

    std::vector<VkDescriptorSetLayoutBinding> layoutBindings; 
    //= { uboLayoutBinding, imageAndSamplerLayoutBinding };
    for ( const auto& slot: std::views::values( descriptorSet.m_slots))
    {
        size_t binding = slot->slotIndexWithinSet;
        VkDescriptorSetLayoutBinding layoutBinding = {};
        layoutBinding.binding = binding;
        layoutBinding.descriptorType = slot->descriptorType;
        layoutBinding.descriptorCount = slot->descriptorCount;
        layoutBinding.stageFlags = slot->stageFlags;
        layoutBinding.pImmutableSamplers = nullptr;
        
        layoutBindings.push_back(layoutBinding);
    }


    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo = {};
    descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetLayoutInfo.bindingCount = static_cast<uint32_t>(layoutBindings.size());
    descriptorSetLayoutInfo.pBindings = layoutBindings.data();

    VkResult createDescriptorSetLayoutResult = vkCreateDescriptorSetLayout( logDev, &descriptorSetLayoutInfo, nullptr, &descriptorSet.m_descriptorSetLayout );
    if ( createDescriptorSetLayoutResult != VK_SUCCESS )
    {
        int foo = 1;
    }
}


void Renderer::allocateToDescriptorSet( const VkDevice& logDev, const VkDescriptorPool& descriptorPool,VkDescriptorSetLayout& descriptorSetLayout, VkDescriptorSet& descriptorSet)
{
    CRAYON_ASSERT( descriptorSetLayout != VK_NULL_HANDLE );

    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.pNext = nullptr;
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    //using the pool we just set
    allocInfo.descriptorPool = descriptorPool;
    //only 1 descriptor set
    allocInfo.descriptorSetCount = 1;
    //using the global data layout
    allocInfo.pSetLayouts = &descriptorSetLayout;

    vkAllocateDescriptorSets( logDev, &allocInfo, &descriptorSet );

}

void Renderer::allocateToDescriptorSets( const VkDevice& logDev, const VkDescriptorPool& descriptorPool, DescriptorSuperset& superSet )
{
    for ( auto& set : superSet.m_sets )
    {
        allocateToDescriptorSet( logDev, descriptorPool, set->m_descriptorSetLayout, set->m_descriptorSet );
    }
}



//returns the index of a suitable memory type within a VkPhysicalDeviceMemoryProperties' "memTypes" field
//NB! I had an absolutely horrendous bug come up with this. Because VkMemoryPropertyFlags is just a uint32_t, you've got 2 uint32_ts,
//so the compiler won't complain if you get your 2 arguments mixed up. Not sure how you'd avoid this... is there a way to make it
//stricter?
uint32_t Renderer::findMemTypeIndex( VkMemoryPropertyFlags wantedProperties, uint32_t typeFilter )
{

    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties( m_physDev, &memProperties );

    //property flags: indicate what a certain type of memory can do

    for ( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
    {
        //if that memory type is one of the ones specified by the type filter...
        if ( (typeFilter & (1 << i)) )
        {
            //...and that memory type has all of the wanted properties...
            if ( (memProperties.memoryTypes[i].propertyFlags & wantedProperties)  == wantedProperties )
            {
                //...then choose that one
                return i;
            }
        }
    }
    //no suitable memory found!
    CRAYON_ASSERT( false );
    return 0;
}

//end of findMemTypeIndex()



//Creates a buffer, which is pretty simple: we just need to know how big it is, and what it's going to be used for.
//Then we assign device memory to it. The assigned memory then gets bound to the logical device. After that, we don't do anything with the
//device memory, though we need to keep a reference to it so that we can free it when the program exits.
void Renderer::createVmaBuffer( VkDeviceSize bufferSize, VkBufferUsageFlags buffUseFlags, AllocatedBuffer& allocatedBuffer, VmaMemoryUsage usage )
{
    allocatedBuffer.size = static_cast<size_t>(bufferSize);
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = buffUseFlags;
    //we never really want to share between queues unless we're doing something really fancy
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VmaAllocationCreateInfo vmaAllocInfo = {};
    vmaAllocInfo.usage = usage;

    vmaCreateBuffer( m_vmaAllocator, &bufferInfo, &vmaAllocInfo, &allocatedBuffer.buffer, &allocatedBuffer.allocation, nullptr );
}





void Renderer::createVmaBuffer( VkDeviceSize bufferSize, VkBufferUsageFlags buffUseFlags, AllocatedBuffer& allocatedBuffer, VkMemoryPropertyFlags memoryPropertyFlags, VmaAllocationCreateFlags allocationCreateFlags)
{
    /*
    VkBufferUsageFlags: the usage of the buffer ("we'll be storing data in this")

    VkMemoryPropertyFlags: specify memory TYPE ("we want this to be visible to the CPU")

    VmaAllocationCreateFlags: how should VMA allocate memory? ("keep this memory mapped because I'm going to be updating it from the cpu the whole time") Not currently used but you will if you need to create an always-mapped buffer etc.

    !!!For the VmaAllocationCreateFlags, VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT or VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT is OBLIGATORY if you want to be able to map the memory (i.e., if this is a staging buffer that you're writing to from the cpu)
    */


    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = buffUseFlags;
    //we never really want to share between queues unless we're doing something really fancy
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VmaAllocationCreateInfo vmaAllocInfo = {};
    vmaAllocInfo.usage = VMA_MEMORY_USAGE_AUTO;

    //the naming here is OUTRAGEOUS: you'd think that 'flags' and 'requiredFlags' would be the same type, right? As in, flags would be all of the flags that are desired, and then requiredFlags would specify the absolutely essential ones.
    //Nope! They're completely different things: flags == VmaAllocationCreateFlags, 'requiredFlags' == VkMemoryPropertyFlags
    vmaAllocInfo.flags = allocationCreateFlags;
    vmaAllocInfo.requiredFlags = memoryPropertyFlags;

    VkResult bufferCreateResult=  vmaCreateBuffer( m_vmaAllocator, &bufferInfo, &vmaAllocInfo, &allocatedBuffer.buffer, &allocatedBuffer.allocation, nullptr );

    CRAYON_ASSERT( bufferCreateResult == VK_SUCCESS && "There was a problem creating a vma buffer" );
}

//maps the buffer destination memory with some memory on the cpu
//puts data in that cpu memory
//unmaps it
//so this is used for getting data from the cpu into something like a staging buffer
void Renderer::mapMemory( AllocatedBuffer dstBuffer, void* data, size_t size, size_t offsetWithinDestination )
{
    void* mappedCPUMem;
    vmaMapMemory( m_vmaAllocator, dstBuffer.allocation, &mappedCPUMem );

    memcpy( static_cast<char*>(mappedCPUMem)+offsetWithinDestination,  data , size );

    vmaUnmapMemory( m_vmaAllocator, dstBuffer.allocation );
}
void Renderer::createCameraBufferAndUpdateDescriptorSet()
{
    VkPhysicalDeviceProperties properties{};
    vkGetPhysicalDeviceProperties( m_physDev, &properties );
    //This is the like the 'grid size' that our gpu wants to use. We want our uniform data to start at a multiple of this.
    //So, if our struct is 4 bytes big and our minUboAligment is 10 bytes, we want to start at 10 bytes.
    size_t minUboAlignment = properties.limits.minUniformBufferOffsetAlignment;



    //we can achieve this easily: if we divide our struct size by our min aligment, we'll get 'How many full min aligments we were able to fit into this struct'. If the 2 don't divide cleanly, then you'll always want 1 more min aligment. I.e. if you're left between 2 multiples of minAligment, you'll want to jump up to the next multiple of minAligment.
    //So let's say struct size = 4, minAlign = 10. 4/10 = 0 (integer divison). So we want 1 min alignment, i.e. we want to start at 10.
    //Or let's say struct size = 25, minAlign = 10. 25/10 = 2: we were able to fit 2 whole 10s in, but it wasn't clean, so we want 3 whole 10s i.e. 30.
    DescriptorSlot& slot = *m_cameraBufferDescriptorSlot; 
    if ( minUboAlignment > 0 )
    {
        if ( slot.baseTypeSize % minUboAlignment != 0 )
        {
            slot.dynamicAlignment = ((slot.baseTypeSize / minUboAlignment) + 1) * minUboAlignment;
        }
        else
        {
            slot.dynamicAlignment = slot.baseTypeSize;
        }
    }


    //create camera buffer, 
    {
        //1: allocate the actual buffer
        const VkDeviceSize uniformBufferSize = slot.dynamicAlignment * FRAME_OVERLAP;
        createVmaBuffer( uniformBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, m_cameraBuffer, VMA_MEMORY_USAGE_CPU_TO_GPU );
        m_allocatedBuffers.push_back( m_cameraBuffer );

        updateDescriptorSlot( m_logDev, *m_cameraBufferDescriptorSlot, m_cameraBuffer.buffer );

    }


}
void Renderer::createStorageImagesAndUpdateDescriptorSet()
{
        //generate the information for the staging buffer images that we'll be setting our descriptors to point to
    std::vector<VkDescriptorImageInfo> descriptorImageInfoStructs(m_frameDataStructs.size());
    for ( size_t i = 0; i < m_frameDataStructs.size(); i++ )
    {
        descriptorImageInfoStructs[i].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
        descriptorImageInfoStructs[i].imageView = m_frameDataStructs[i].preprocessingImage.imageView;
        descriptorImageInfoStructs[i].sampler = VK_NULL_HANDLE;
    }
    DescriptorSlot& slot = *m_preprocessedImageBufferDescriptorSlot;//set.getSlot( UNPROCESSED;
    DescriptorSet& set = *slot.owningSet;//*m_stagingImagesDescriptorSet; 
    size_t slotBinding = set.getSlotIndex( UNPROCESSED_IMAGES_SLOT_NAME );
    VkWriteDescriptorSet writeToSetInfoStruct = {};

    writeToSetInfoStruct.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeToSetInfoStruct.dstSet = set.m_descriptorSet;
    writeToSetInfoStruct.dstBinding = slotBinding;
    writeToSetInfoStruct.dstArrayElement = 0;
    writeToSetInfoStruct.descriptorType = slot.descriptorType;
    writeToSetInfoStruct.descriptorCount = descriptorImageInfoStructs.size();
    writeToSetInfoStruct.pImageInfo = descriptorImageInfoStructs.data();

    vkUpdateDescriptorSets( m_logDev, 1, &writeToSetInfoStruct, 0, nullptr );
}
void Renderer::setUpPipelines()
{
    //SET UP PIPELINES

    VkPipelineInputAssemblyStateCreateInfo lineInputAssemblyState = {};
    lineInputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    lineInputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    lineInputAssemblyState.primitiveRestartEnable = VK_FALSE;



    //set up push constants
    //Following tutorial used when implementing push constants:
    // Galea, B., 2020. Push Constants - Vulkan Game Engine Tutorial 09.
    // [video] Available at: <https://youtu.be/wlLGLWI9Fdc> [Accessed 14 April 2022].
    auto initPushConstantRange = []( size_t structSize )
        {
            VkPushConstantRange range = {};
            range.stageFlags = ALL_USED_SHADER_STAGES;
            range.offset = 0;
            range.size = structSize;
            return range;
        };


    //to do: make the target format part of the CrayonPipeline class
    //To Do: also, pass in the target resource instead of passing in STAGING_IMAGE_FORMAT or whatever directly
    initPipeline( m_spritePipeline, "SpritePipeline", ShaderType::MESH, m_logDev, initPushConstantRange( sizeof( Sprite ) ), STAGING_IMAGE_FORMAT, true );

    initPipeline( m_solidShapePipeline, "SolidShapePipeline", ShaderType::MESH, m_logDev,  initPushConstantRange( sizeof( Rect ) ), STAGING_IMAGE_FORMAT, true );

    initPipeline( m_uiSpritePipeline, "UISpritePipeline", ShaderType::MESH, m_logDev,  initPushConstantRange( sizeof( Sprite ) ), STAGING_IMAGE_FORMAT, true);

    initPipeline( m_linePipeline, "LinePipeline", ShaderType::MESH, m_logDev,  initPushConstantRange( sizeof( RenderableLine ) ), STAGING_IMAGE_FORMAT, true);

    initPipeline( m_circlePipeline, "CirclePipeline", ShaderType::MESH, m_logDev,  initPushConstantRange( sizeof( Rect ) ), STAGING_IMAGE_FORMAT, true );

    initPipeline( m_colorCorrectionPipeline, "ColorCorrectionPipeline", ShaderType::MESH, m_logDev,  initPushConstantRange( sizeof( ColorCorrectionPushStruct ) ), m_surfaceFormat.format, false);

    initPipeline( m_spriteBatchPipeline, "SpriteBatchPipeline", ShaderType::MESH, m_logDev, initPushConstantRange( sizeof( BufferRange ) ), STAGING_IMAGE_FORMAT, true );


}
void Renderer::setUpAllocator( const VkInstance& vulkanInstance, const VkDevice& logDev, const VkPhysicalDevice& physDev, VmaAllocator& allocator )
{

    //Now that we're going to start dealing with buffers and images over on the cpu, we need to set up VMA
    VmaAllocatorCreateInfo allocatorCreateInfo = {};
    allocatorCreateInfo.physicalDevice = physDev;
    allocatorCreateInfo.device = logDev;
    allocatorCreateInfo.instance = vulkanInstance;

    vmaCreateAllocator( &allocatorCreateInfo, &allocator );
}
;


//create an image (which doesn't actually allocate any memory in itself),
//then allocate memory to it, then bind the two together.
//(pretty similar to creating a buffer)
void Renderer::createImage( uint32_t width, uint32_t height, VkFormat& format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags memoryProperties,
    VkImage& image, VmaAllocation& allocation )
{
    VkImageCreateInfo imageCreateInfo = {};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
    //"extent": how many texels there are on a given axis
    imageCreateInfo.extent.width = static_cast<uint32_t>(width);
    imageCreateInfo.extent.height = static_cast<uint32_t>(height);
    imageCreateInfo.extent.depth = 1;
    imageCreateInfo.mipLevels = 1;
    imageCreateInfo.arrayLayers = 1;
    //This has to match the format of the pixels in the staging buffer
    imageCreateInfo.format = format;
    //vkTutorial: "If you want to be able to directly access texels in the memory of the image, then you 
    //must use VK_IMAGE_TILING_LINEAR. We will be using a staging buffer instead of a staging image, so this won't be necessary."
    imageCreateInfo.tiling = tiling;
    imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageCreateInfo.usage = usage;
    imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    //this is used when you're multisampling (i.e. in antialiasing)
    imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageCreateInfo.flags = 0;
    
    VmaAllocationCreateInfo imageAllocInfo = {};
    imageAllocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

    VkResult createImageResult= vmaCreateImage( m_vmaAllocator, &imageCreateInfo, &imageAllocInfo, &image,
        &allocation, nullptr );

    CRAYON_ASSERT( createImageResult == VK_SUCCESS );

}
//end of createImage()

//creates a temporary command buffer.
//'begins' the buffer (you need to do this before you start recording to it)
//If you're wondering what makes this "temporary", we plug VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT into its beginInfo
VkCommandBuffer Renderer::beginTempComBuffer()
{
    VkCommandBufferAllocateInfo tempComBuffInfo = {};
    tempComBuffInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    tempComBuffInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    tempComBuffInfo.commandPool = getCurrentFrame().commandPool;
    tempComBuffInfo.commandBufferCount = 1;

    VkCommandBuffer tempCommandBuffer;
    VkResult allocTempComBuffResult = vkAllocateCommandBuffers( m_logDev, &tempComBuffInfo, &tempCommandBuffer );
    CRAYON_ASSERT( allocTempComBuffResult == VK_SUCCESS );

    VkCommandBufferBeginInfo tempCBBeginInfo = {};
    tempCBBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    tempCBBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer( tempCommandBuffer, &tempCBBeginInfo );

    return tempCommandBuffer;
}

//.'ends' the command buffer so you stop recording to it
//.sumbits it to the queue
//.waits until the queue has finished doing whatever was in the command buffer (and everything else)
//.frees the command buffer
void Renderer::useUpTempComBuffer( VkCommandBuffer tempComBuffer )
{
    vkEndCommandBuffer( tempComBuffer );

    VkSubmitInfo tempCBSubmitInfo = {};
    tempCBSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    tempCBSubmitInfo.commandBufferCount = 1;
    tempCBSubmitInfo.pCommandBuffers = &tempComBuffer;

    vkQueueSubmit( m_graphicsQueue, 1, &tempCBSubmitInfo, VK_NULL_HANDLE );
    //We could use a fence and wait with vkWaitForFences, or simply wait for the transfer queue to become idle with vkQueueWaitIdle.

    //Now we want to wait for all of the commands to have been executed
    vkQueueWaitIdle( m_graphicsQueue );

    vkFreeCommandBuffers( m_logDev, getCurrentFrame().commandPool, 1, &tempComBuffer );
}



//create a temporary command buffer.
//'begin' the buffer (you need to do this before you start recording to it)
//use vkCmdCopyBuffer to copy data from one gpu buffer to another
//'end' the command buffer and submit it to the queue
//wait for the queue to finish up
//free the temporary command buffer
void Renderer::copyBuffer( VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size )
{
    VkCommandBuffer commandBuffer = beginTempComBuffer();
    VkBufferCopy copyRegion = {};
    copyRegion.srcOffset = 0; // Optional
    copyRegion.dstOffset = 0; // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer( commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion );

    useUpTempComBuffer( commandBuffer );
}

void Renderer::updateCameraPosition()
{
    //create a new model-view-projection matrix for the camera, then copy it over to gpu-visible memory
    MVP mvp = getCameraAsMvp();

    size_t mvpSize = sizeof( MVP );

    const DescriptorSlot& cameraSlot = *m_cameraBufferDescriptorSlot;
    size_t offset = m_currentFrameNumber % FRAME_OVERLAP * cameraSlot.dynamicAlignment;

    mapMemory( m_cameraBuffer, (void*)&mvp, sizeof(MVP), offset);
}

//.loads pixels in from a file, then stores them in an image.
//.this process involves going via a staging buffer and transitioning the layout of the image to first receive incoming data most efficiently, and then being put in the most efficient layout to read
ImageResource Renderer::loadTexture_fileToGPU ( const char* fileName )
{
       ImageResource newTexture;
    
        //1: convert the png to a pointer to an array of pixels in the cpu memory
        int texWidth=0;
        int texHeight=0;
        int texChannels=0;
        //STBI_rgb_alpha value forces the image to be loaded with an alpha channel, even if it doesn't have one
        //so, with STBI_rgb_alpha we're saying what channels we want, and the actual texChannels variable is there to record
        //the number of channels that are actually available in the image
        const int pixelFormat = STBI_rgb_alpha;
        stbi_uc* pixels = stbi_load( fileName, &texWidth, &texHeight, &texChannels, pixelFormat);
        CRAYON_ASSERT( pixels );

        //2 create (but don't fill) a staging buffer
        //The pixels are laid out row by row with 4 bytes per pixel in the case of STBI_rgb_alpha
        size_t imageSize = static_cast<size_t>(texWidth) * static_cast<size_t>(texHeight) * static_cast<size_t>( pixelFormat );
        //staging buffer + mem: the staging buffer where we'll be putting our pixel data before transferring it over to the image
        AllocatedBuffer stagingBuffer;
        createVmaBuffer( imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, stagingBuffer, VMA_MEMORY_USAGE_CPU_TO_GPU );

        //3 transfer the pixel data over to the staging buffer
        mapMemory( stagingBuffer, (void*)pixels, imageSize );
        stbi_image_free( pixels );

        newTexture.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;

        //4 create the image (and allocate memory to it), but don't transfer pixel data over to it yet
        createImage( texWidth, texHeight, newTexture.imageFormat, VK_IMAGE_TILING_OPTIMAL, 
            VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            newTexture.image, newTexture.imageAllocation);

        //5 creates an imageMemoryBarrier that translates the image from one format to another (and also creates a command buffer
        //to insert that barrier into the queue, then waits for the queue to be idle)
        //NB it's a bit odd that you have to transition the layout of the image - that you haven't copied any data into
        //yet- before you copy that data across. Couldn't we have just created the image in that VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
        //layout to begin with?
        //And what are we actually changing the layout of? I guess just the data that tells you about the image, rather
        //than the actual image data itself
        transitionImageLayout( newTexture.image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL );

        //////////////////////////////////////////////////
        // THIS IS WHERE WE ACTUALLY WRITE TO THE FINAL DESTINATION
        // ////////////////////////////////////////////////
        //6: inserts a vkCmdCopyBufferToImage command, and deals with temp command buffer stuff around that
       copyBufferToImage( stagingBuffer.buffer, newTexture.image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
        //7: transition the image to the most efficient layout to read from
        transitionImageLayout( newTexture.image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        vmaDestroyBuffer( m_vmaAllocator, stagingBuffer.buffer, stagingBuffer.allocation );

        newTexture.imageDimensions = glm::vec2( texWidth, texHeight );

    return newTexture;

}


//creates a temporary command buffer
//creates an imageMemoryBarrier
//creates a command that inserts the imageMemoryBarrier
//submits that temporary command buffer and waits for it to have been executed
void Renderer::transitionImageLayout( VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout )
{
    VkCommandBuffer commandBuffer = beginTempComBuffer();

    VkImageMemoryBarrier2 imageBarrier2{};
    imageBarrier2.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;

    //set up stage and access masks
    //stage mask: when in the pipeline synch happens
    //access mask: what sort of memory needs to be synched (like, what sort of memory operations are relevant here: reads? writes? etc.)
    //Before the synch2 extension, these used to be passed in separately (the stage and access masks), despite being so intimately linked, but now we bundle them all up in the same barrier object.
    if ( oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL )
    {
        //source stage: the stage we'll wait to have completed before we do this stuff
        imageBarrier2.srcStageMask = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT;
        imageBarrier2.srcAccessMask = VK_ACCESS_2_NONE;
        
        //the destination stage - the stage that needs to wait until the transition is done
        imageBarrier2.dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT;
        imageBarrier2.dstAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT;
    }

    //In other words, this stuff is saying:
    //"Don't do this following chunk of commands until write operations in the transfer stage are over, and don't let anything after this chunk of commands do read operations in the fragment shader stage until this chunk of commands has finished"
    else if ( oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL )
    {
        //source stage: the stage we'll wait to have completed before we do this stuff
        imageBarrier2.srcStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT;
        imageBarrier2.srcAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT;

        //the destination stage - the stage that needs to wait until the transition is done
        imageBarrier2.dstStageMask = VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT;
        imageBarrier2.dstAccessMask = VK_ACCESS_2_SHADER_READ_BIT;
    }

    else
    {
        //invalid layout combination
        CRAYON_ASSERT( false );
    }

    imageBarrier2.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imageBarrier2.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    imageBarrier2.oldLayout = oldLayout;
    imageBarrier2.newLayout = newLayout;

    imageBarrier2.image = image;

    imageBarrier2.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageBarrier2.subresourceRange.baseMipLevel = 0;
    //number of mipmap levels used
    imageBarrier2.subresourceRange.levelCount = 1;
    imageBarrier2.subresourceRange.baseArrayLayer = 0;
    imageBarrier2.subresourceRange.layerCount = 1;


    VkDependencyInfo dependencyInfo{};
    dependencyInfo.sType= VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    dependencyInfo.imageMemoryBarrierCount = 1;
    dependencyInfo.pImageMemoryBarriers = &imageBarrier2;

    vkCmdPipelineBarrier2( commandBuffer, &dependencyInfo );

    useUpTempComBuffer( commandBuffer );
}


//really a wrapper around vkCmdCopyBufferToImage, except that's a command so we have to set up a temp command buffer
//for it, submit and clear that command buffer etc.
// we also use useUpTempComBuffer() at the end, so we'll wait until the queue is idle before returning
//we also need to supply info abt. the region of the buffer we're copying into the image, which we'll just hardcode here
//to be the whole thing
void Renderer::copyBufferToImage( VkBuffer buffer, VkImage image, uint32_t width, uint32_t height )
{
    VkCommandBuffer commandBuffer = beginTempComBuffer();

    //up in copyBuffer(), we used a VkBufferCopy struct to specify how much of a buffer we wanted to transfer over.
    //It's the basic idea here, just with VkBufferImageCopy
    VkBufferImageCopy region = {};
    //byte offset at which pixel values start
    region.bufferOffset = 0;
    //how pixels are laid out in memory: setting both to 0 means that there is no padding between rows, and the
    //pixels are just tightly packed in together
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    //not sure what the aspectMask is about
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;

    region.imageOffset = { 0, 0, 0 };
    region.imageExtent = 
    {
        width,
        height,
        1
    };

    vkCmdCopyBufferToImage( commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region );
    useUpTempComBuffer( commandBuffer );
}

VkImageView Renderer::createImageView( VkImage image, VkFormat format, VkImageAspectFlags aspectFlags )
{
    //what image do you want to use?
    //how much of it do you want to use?
    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    VkImageView imageView;
    VkResult createImageViewResult = vkCreateImageView( m_logDev, &viewInfo, nullptr, &imageView );
    CRAYON_ASSERT( createImageViewResult == VK_SUCCESS );

    return imageView;
}

//sets up m_textureSampler
void Renderer::createTextureSampler()
{
    //you don't HAVE TO use a sampler... but you pretty much always will.
    
    //The sampler does 2 big jobs:
    
    //1: Filtering-> you can work out want texel a given fragment falls on, but you don't generally want to just go and use that
    //texel's colour directly: you'll want to do a a bilinear interpolations of the colours of the
    //4 texels surrounding the point on the texture a fragment maps to so that you don't get weird, jagged graphics.

    //2: Addressing-> finding that point on the texture in the first place, and more specifically working out what to do if the
    //point actually falls off the edge of the texture.
    //You have to decide how you're going to CLAMP things to the bounds of the texture: are you going to just keep
    //using the texel at the edge, or wrap around etc. etc., and you need to specify this for each axis.


    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;

    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

    //I don't think we need this for a 2d game. Basically, anisotropy seems to be specific to when you're using mipmaps.
    //mipmaps are lower-res textures that you use when the number of pixels being used to draw a shape is smaller than the
    //number of texels in the attached texture. I'd have thought that the same process of filtering would have sorted it out
    //but apparently it's prone to weird visual glitches.
    //Anyway, if the player squats low to the ground, then a sqare on the floor is going to get squashed lengthwise by
    //perspective, so not many pixels will be used to draw it, so a low-res mipmap will be chosen.
    //However, it's only been squashed lengthwise: it's unnaffected across, and now you're using this low-res texture, and it'll
    //look horribly stretched going from left to right. Anisotropic filtering is about getting around this: how, I don't know.

    //if you want to enable anisotropy, then when you're creating the logical device you have to specify that you need it
    samplerInfo.anisotropyEnable = VK_FALSE;

    VkPhysicalDeviceProperties physDevProperties;
    vkGetPhysicalDeviceProperties( m_physDev, &physDevProperties );

    samplerInfo.maxAnisotropy = physDevProperties.limits.maxSamplerAnisotropy;

    //this is irrelevant because of the address modes we're using: this only kicks in when you're clamping to the border
    //(i.e. just not using any info from the texture when you go off the edge of it)
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;

    //in OpenGL, textures always use normalized coordinates in the 0 to 1 range, and this is really good because it means
    //you can put a little texture on a big thing etc. without worrying.
    //You can choose not to do that in Vulkan, but it would be a pain.
    samplerInfo.unnormalizedCoordinates = VK_FALSE;

    //this stuff seems to be related to shadow maps, so we don't need to worry
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

    //mipmap stuff
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;


    VkResult createSamplerResult = vkCreateSampler( m_logDev, &samplerInfo, nullptr, &m_textureSampler );

    CRAYON_ASSERT( createSamplerResult == VK_SUCCESS );
}

FrameData& Renderer::getCurrentFrame()
{
    return m_frameDataStructs[m_currentFrameNumber % FRAME_OVERLAP];
}




//even though we're just dealing with one texture name, we still create a vector of them because
//that's what loadImageDataCreateTextureVector_thenAddm_Textures() expects
size_t Renderer::addTextureIfNew( const char* textureName )
{
    if ( !m_textureIDMap.contains( textureName ) )
    {
        std::vector<const char*> textureNameVector;
        textureNameVector.push_back( textureName );

        loadTexturesAndAddToTextureBinding( textureNameVector );
    }
    return m_textureIDMap[textureName];
}



size_t Renderer::getScreenWidth() const
{
    return m_screenWidth;
}

size_t Renderer::getScreenHeight() const
{
    return m_screenHeight;
}

void Renderer::recreateSwapChainAndUpdateDependencies( HWND winHandle )
{
    //this also updates the m_windowWidth etc.
    //ToDo: you need to make this clear: pass them in as parameters or whatever.
    recreateSwapChain( winHandle );

    cleanUpPreprocessingImagesAndTheirDepthBuffers();

    setUpPreprocessImages( m_vmaAllocator );

    const ImageResource& stagingImageReference = getCurrentFrame().preprocessingImage;
    setUpDepthImages( stagingImageReference.imageDimensions.x, stagingImageReference.imageDimensions.y, false );

    std::vector<VkDescriptorImageInfo> descriptorImageInfoStructs( m_frameDataStructs.size() );
    for ( size_t i = 0; i < m_frameDataStructs.size(); i++ )
    {
        descriptorImageInfoStructs[i].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
        descriptorImageInfoStructs[i].imageView = m_frameDataStructs[i].preprocessingImage.imageView;
        descriptorImageInfoStructs[i].sampler = VK_NULL_HANDLE; // Storage images don’t need samplers
    }

    DescriptorSet& stagingImageSet = *m_preprocessedImageBufferDescriptorSlot->owningSet;
        //*m_stagingImagesDescriptorSet;

    VkWriteDescriptorSet writeToSetInfoStruct = {};
    writeToSetInfoStruct.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeToSetInfoStruct.dstSet =stagingImageSet.m_descriptorSet;
    writeToSetInfoStruct.dstBinding = stagingImageSet.getSlotIndex(UNPROCESSED_IMAGES_SLOT_NAME);
    writeToSetInfoStruct.dstArrayElement = 0;
    writeToSetInfoStruct.descriptorType = stagingImageSet.getSlot( UNPROCESSED_IMAGES_SLOT_NAME ).descriptorType;
    writeToSetInfoStruct.descriptorCount = descriptorImageInfoStructs.size();
    writeToSetInfoStruct.pImageInfo = descriptorImageInfoStructs.data();

    vkUpdateDescriptorSets( m_logDev, 1, &writeToSetInfoStruct, 0, nullptr );

}

void Renderer::recreateSwapChain( HWND winHandle)
{
    vkDeviceWaitIdle(m_logDev);

    cleanUpSwapChain();
    
    createSwapChain( winHandle);

}

//also cleans up image views for swapchain
void Renderer::cleanUpSwapChain()
{

    for ( auto& swapchainImageResource: m_swapchainImageResources)
    {
        CRAYON_ASSERT( swapchainImageResource.imageView != VK_NULL_HANDLE );
        vkDestroyImageView( m_logDev, swapchainImageResource.imageView, nullptr );
        swapchainImageResource.imageView = VK_NULL_HANDLE;
    }

    vkDestroySwapchainKHR( m_logDev, m_swapchain, nullptr );
    m_swapchain = VK_NULL_HANDLE;
}

void Renderer::cleanUpPreprocessingImagesAndTheirDepthBuffers()
{
    for ( auto& frameData : m_frameDataStructs )
    {
        vkDestroyImageView( m_logDev, frameData.preprocessingImage.imageView, nullptr );
        vmaDestroyImage( m_vmaAllocator, frameData.preprocessingImage.image, frameData.preprocessingImage.imageAllocation );

        vkDestroyImageView( m_logDev, frameData.preprocessingDepthBuffer.imageView, nullptr );
        vmaDestroyImage( m_vmaAllocator, frameData.preprocessingDepthBuffer.image, frameData.preprocessingDepthBuffer.imageAllocation );
    }
}



//ToDo: this needs to be split apart, because it doesn't just 'load images to desciptor sets': it actually creates the images over on the gpu, which is a different thing
void Renderer::loadTexturesAndAddToTextureBinding( const std::vector<const char*>& rawTextureNames )
{

    //1: Create a vector of just the textureNames that are actually new.
    size_t currentTextureId = m_textureHandles.size();

    std::vector<const char*> newTextureNames;
    for ( size_t i = 0; i < rawTextureNames.size(); i++ )
    {
        if ( ! m_textureIDMap.contains(rawTextureNames[i]) )
        {
            newTextureNames.push_back( rawTextureNames[i] );

           const char* const newTextureName = newTextureNames[i];
           m_textureIDMap[newTextureName] = currentTextureId++;
        }
    }

    //2: check that there are some actual new texture names
    if ( newTextureNames.size() < 1 )
    {
        return;
    }

    //3: Create a bunch of Images and ImageViews for these textures over on the GPU. Store them in TextureHandle structs, that tie together the Image with the ImageView.

    //create the images and bundle them up in texture handles
    std::vector<ImageResource> newTextureHandles( newTextureNames.size() );
    for ( size_t i = 0; i < newTextureNames.size(); i++ )
    {
        newTextureHandles[i] = loadTexture_fileToGPU( newTextureNames[i] );
    }
   
    //create the image views, and add those to the texture handles
    for ( size_t i = 0; i < newTextureHandles.size(); i++ )
    {
        newTextureHandles[i].imageView = createImageView( newTextureHandles[i].image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT );
    }

    updateTextureDescriptors( newTextureHandles );


    //finally, add the newTextureHandles to the old ones
    for ( size_t i = 0; i < newTextureHandles.size(); i++ )
    {
        m_textureHandles.push_back( newTextureHandles[i] );
    }

}

void Renderer::updateTextureDescriptors( std::vector<ImageResource>& newTextureHandles )
{
    //4: Now we get onto updating the desciptor set

  //generate the actual image information for each image: view, sampler, layout
    std::vector<VkDescriptorImageInfo> descriptorImageInfoStructs( newTextureHandles.size() );
    for ( size_t i = 0; i < descriptorImageInfoStructs.size(); i++ )
    {
        descriptorImageInfoStructs[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        descriptorImageInfoStructs[i].imageView = newTextureHandles[i].imageView;
        descriptorImageInfoStructs[i].sampler = m_textureSampler;
    }

    //the info about the descriptors: what set, what binding, where from (we only need one of these: the starting point from where we'll copy in a bunch of images)
    VkWriteDescriptorSet writeToSetInfoStruct = {};

    CRAYON_ASSERT( m_textureArrayDescriptorSlot->owningSet != nullptr );
    DescriptorSet& descriptorSet = *m_textureArrayDescriptorSlot->owningSet;//*m_globalDescriptorSet;//m_descriptorSuperset.getSet( GLOBAL_DE;
    DescriptorSlot& descriptorSlot = descriptorSet.getSlot( TEXTURE_ARRAY_SLOT_NAME );
    size_t textureArraySlotIndex = descriptorSet.getSlotIndex( TEXTURE_ARRAY_SLOT_NAME );

    writeToSetInfoStruct.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeToSetInfoStruct.dstSet = descriptorSet.m_descriptorSet;
    writeToSetInfoStruct.dstBinding = textureArraySlotIndex;
    writeToSetInfoStruct.dstArrayElement = static_cast<uint32_t>(m_textureHandles.size());
    writeToSetInfoStruct.descriptorType = descriptorSlot.descriptorType;
    writeToSetInfoStruct.descriptorCount = descriptorImageInfoStructs.size();
    writeToSetInfoStruct.pImageInfo = descriptorImageInfoStructs.data();


    vkUpdateDescriptorSets( m_logDev, 1,
        &writeToSetInfoStruct, 0, nullptr );


}


ImageResource& Renderer::getTextureHandle( size_t textureIndex )
{
    return m_textureHandles[textureIndex];
}

void Renderer::setUpPreprocessImages( VmaAllocator& allocator )
{
    for ( auto& frameDataStruct : m_frameDataStructs )
    {
        CRAYON_ASSERT( m_vmaAllocator != VK_NULL_HANDLE );
        //To Do: bundle this info up in the DescriptorGroup stuff, and come up with specific combinations for certain kinds of images (staging images, etc.)
        //get rid of STAGING_IMAGE_FORMAT
        frameDataStruct.preprocessingImage.imageFormat = STAGING_IMAGE_FORMAT;
        VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |/* VK_IMAGE_USAGE_SAMPLED_BIT|*/ VK_IMAGE_USAGE_STORAGE_BIT;


        frameDataStruct.preprocessingImage.imageDimensions.x = m_screenWidth;
        frameDataStruct.preprocessingImage.imageDimensions.y = m_screenHeight;


        createImage( m_screenWidth, m_screenHeight, frameDataStruct.preprocessingImage.imageFormat, VK_IMAGE_TILING_OPTIMAL, usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, frameDataStruct.preprocessingImage.image, frameDataStruct.preprocessingImage.imageAllocation );

        frameDataStruct.preprocessingImage.imageView= createImageView( frameDataStruct.preprocessingImage.image, STAGING_IMAGE_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT );
    }
}

void Renderer::setCameraPosition( float x, float y )
{
    m_cameraPosition = { x,y };
}

void Renderer::setCameraPosition( glm::vec2 newPos )
{
    m_cameraPosition = newPos;
}

glm::vec2 Renderer::getCameraPosition2D() const
{
    return m_cameraPosition;
}

float Renderer::getCameraX() const
{
    return m_cameraPosition.x;
}

float Renderer::getCameraY() const
{
    return m_cameraPosition.y;
}

//ToDo:
//things we have baked in here:
//-> all the descriptor set stuff: as in, I think you can only have 1? which is... insane

//the basic idea: you set up the lightweight stuff yourself, and then initPipeline takes care of creating the pipelineLayout and pipeline handles.
//Currently, this doesn't allow you to share any big, heavy handle-type stuff, like re-using pipelineLayouts across multiple Pipelines, but we'll change this soon.
//For now, the whole benefit of the Pipeline is really just that it bundles together the info needed to create a pipeline, and it takes care of cleaning up those resources.
void Renderer::initPipeline( Pipeline& pipeline, const std::string& name, ShaderType shaderType, const VkDevice& logDev, VkPushConstantRange pushConstantRange, VkFormat targetFormat, bool usesDepthBuffer)
{

    //Set up SPECIFICS

    //Always different
    pipeline.m_name = name;

    pipeline.m_logDev = m_logDev;

    pipeline.m_shaderType = shaderType;


    //Possibly Shared
    //Input Assembly Info used to set up Pipeline, not PipelineLayout.
    //Mesh shaders don't use InputAssemblyState stuff, so leave it out.
    pipeline.m_pushConstantRange = pushConstantRange;

    pipeline.m_usesDepthBuffer = usesDepthBuffer;

    createPipelineLayout( pipeline.m_pipelineLayout, pipeline.m_pushConstantRange);



    const char* spvFolderPath = "Shaders/spvFiles/";
    pipeline.m_pushConstantShaderStageFlags = ALL_USED_SHADER_STAGES;
    
    loadShaderModule( (spvFolderPath + pipeline.m_name + "_mesh.spv").c_str(), &pipeline.m_meshShadMod );
    loadShaderModule( (spvFolderPath + pipeline.m_name + "_frag.spv").c_str(), &pipeline.m_fragShadMod );
    createPipeline( pipeline, targetFormat, 1.f );

    pipeline.m_initialized = true;

    m_pipelines.push_back( &pipeline );
}

MVP Renderer::getCameraAsMvp() const
{
    MVP mvp = {};

    //the model model matrix takes points and puts them in world space, but our camera is just a single point
    //and its position already directly represents it in world space, so we'll just set an identity matrix
    //for this part
    mvp.model = {};

    glm::vec3 cameraPos( m_cameraPosition, 0.f );

    //the view matrix converts points in world space to view space. Here, we want the inverse,
    //because we're not converting the point representing the camera, but everything else relative to that point
    mvp.view = glm::inverse( glm::translate( glm::mat4( 1.f ), cameraPos ) );

    //the projection matrix converts from the view space to normalized device coordinates
    float halfScreenWidth = m_screenWidth * 0.5f;
    float halfScreenHeight = m_screenHeight * 0.5f;
    mvp.proj = glm::ortho( -halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight );
    return mvp;
}



//go from normalized device coordinates to worldspace
glm::vec2 Renderer::getScreenToWorld( glm::vec2 screenspaceVector ) const
{

    MVP mvp = getCameraAsMvp();
    glm::mat4 inverseViewMatrix = glm::inverse( mvp.view );
    glm::mat4 inverseProjectionMatrix = glm::inverse( mvp.proj );

    glm::vec4 viewSpaceVector = inverseProjectionMatrix * glm::vec4{ screenspaceVector.x, screenspaceVector.y, 0.f, 1.f };
    glm::vec4 worldSpaceVector = inverseViewMatrix * viewSpaceVector;

    return glm::vec2(worldSpaceVector);
}

glm::vec2 Renderer::getPixelsToNdcs( glm::ivec2 pixelScreenCoord ) const
{
    glm::vec2 ndcs{};
    ndcs.x= static_cast<float>(pixelScreenCoord.x) / static_cast<float>(m_screenWidth);
    ndcs.y = static_cast<float>(pixelScreenCoord.y) / static_cast<float>(m_screenHeight);
    ndcs *= 2.f;
    ndcs -= glm::vec2( 1.f, 1.f );
    return ndcs;
}


void Renderer::drawColourCorrection()
{
    ColorCorrectionPushStruct colorCorrectionPush;
    colorCorrectionPush.pushFrameData.currentFrameIndex = m_currentFrameNumber % FRAME_OVERLAP;
    colorCorrectionPush.brightness = brightness;
    colorCorrectionPush.contrast = contrast;
    colorCorrectionPush.saturation = 1.f;

    std::vector<ColorCorrectionPushStruct> colorCorrectionPushVector{ colorCorrectionPush };

    draw<ColorCorrectionPushStruct>( m_colorCorrectionPipeline, colorCorrectionPushVector );
}



}