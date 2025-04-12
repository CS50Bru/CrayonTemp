#pragma once

//I'm putting this in the header file because any part of our code that is interacting directly with the Renderer needs have its glm set up accordingly
#define GLM_FORCE_RADIANS
//Vulkan depth range = 0 to 1, opengl = -1 to 1
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include<array>
#include<unordered_map>
#include<ranges>
#include<vector>
#include<Windows.h>

#include"AllocatedBuffer.h"
#include"Libraries/glm/glm.hpp"
#include"Libraries/vma/vk_mem_alloc.h"
#include"MVP.h"
#include"Sprite.h"
#include"RenderableLine.h"
#include"Rect.h"
#include"Core.h"
#include"Pipeline.h"
#include"RenderingSettings.h"
#include"DescriptorSlot.h"

namespace Crayon
{

	struct PushFrameData
	{
		uint32_t currentFrameIndex = 0;
	};

	struct ColorCorrectionPushStruct
	{
		PushFrameData pushFrameData;
		float contrast = 1.f;
		//brightness 0.f = unchanged
		float brightness = 0.f;
		float saturation = 1.f;
	};



	enum class ImageResourceType
	{
		Texture,
		Attachment
	};

	struct BufferRange
	{
		uint32_t start = 0;
		uint32_t count = 0;
	};



	struct ImageResourceUsage
	{
		VkImageLayout layoutForUsage;
		VkAccessFlagBits2 usage;
		VkPipelineStageFlags usageStages;
		VkAttachmentLoadOp loadOp;
		VkAttachmentStoreOp storeOp;
		ImageResourceType resourceType;
		VkRect2D renderArea;
		bool firstPass = false;
		bool useAsDepthBuffer = false;
	};



	

	struct ImageResource
	{
		VkImage image = VK_NULL_HANDLE;
		VkImageView imageView = VK_NULL_HANDLE;
		VmaAllocation imageAllocation;

		//Unchanging: these could be shared between our different PreprocessingImages etc.
		VkFormat	imageFormat = VK_FORMAT_UNDEFINED;
		VkFormat	viewFormat = VK_FORMAT_UNDEFINED;
		glm::uvec2	imageDimensions{};
		uint32_t	baseMipLevel = 0;
		uint32_t	levelCount = 1;
		uint32_t	baseArrayLayer = 0;
		uint32_t	layerCount = 1;


		VkImageLayout currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		VkPipelineStageFlags latestUsageStage = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT;
		VkAccessFlags2 latestAccessType = VK_ACCESS_2_NONE;

		//To do: if the below is right, then I think we need to move 'aspectflags' to ImageResourceUsage
		//as far as I can tell, aspect flags are mostly used for pipeline barriers: they specify the data within an image being used
		VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
	};

	//to do: currently just used to pass information to the GuiManager, but maybe a useful thing to have around?
	struct AttachmentGroup
	{
		VkFormat mainAttachmentFormat = {};
		VkFormat depthBufferFormat = {};
		bool usesDepthBuffer = false;
	};


	struct FrameData
	{
	public:
		VkSemaphore imageAvailableSempahore = VK_NULL_HANDLE;
		VkSemaphore imageRenderedToSemaphore = VK_NULL_HANDLE;

		VkSemaphore commandBufferFreeSemaphore = VK_NULL_HANDLE;

		VkCommandPool commandPool = VK_NULL_HANDLE;
		VkCommandBuffer mainCommandBuffer = VK_NULL_HANDLE;

		//make sure to update this each time you start drawing a new frame!
		uint32_t currentSwapChainImageIndex_NOTFrameDataIndex = 0u;

		uint64_t commandBufferFreeTimelineValue = 0u;

		ImageResource preprocessingImage{};
		ImageResource preprocessingDepthBuffer{};


	};

	class Renderer
	{
	private:

		//ToDo: why are these string and not string_views?
		std::string GLOBAL_DESCRIPTOR_SET_NAME = "GlobalDescriptorSet";
		std::string STAGING_IMAGES_DESCRIPTOR_SET_NAME = "StagingImagesDescriptorSet";

		std::string CAMERA_BUFFER_SLOT_NAME = "CameraBufferSlot";
		std::string TEXTURE_ARRAY_SLOT_NAME = "TextureArraySlot";
		std::string UNPROCESSED_IMAGES_SLOT_NAME = "UnprocessedImagesSlot";

		//ToDo: get rid of these (we'll load them in from a settings file instead)
		float brightness = 0.f;
		float contrast = 1.f;
		//using CrayonDescriptorSetInfo = std::vector<CrayDescriptorSlot>;

		static constexpr VkShaderStageFlags ALL_USED_SHADER_STAGES = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_MESH_BIT_EXT;

		static constexpr size_t FRAME_OVERLAP = 2;

		static constexpr size_t MAX_SPRITES = 1000000;// the max number of Sprite structs we'll have in the buffer of sprites we use for batch rendering.

		static constexpr VkFormat STAGING_IMAGE_FORMAT = VK_FORMAT_B8G8R8A8_UNORM;

		static constexpr VkFormat DEPTH_BUFFER_DEFAULT_FORMAT = VK_FORMAT_D16_UNORM;

		static constexpr uint32_t meshShaderMaxVertexOutput = 256;

		static constexpr uint32_t meshShaderMaxPrimitiveOutput = 256;

		//ToDo:
		//for now, I hardcode the maximum number of textures inside the shaders to 100. In the future, it would be much better to make this
		//dynamic but I'll have to work out how.
		static constexpr uint32_t MAX_TEXTURE_COUNT = 100;

		//LunarG: application->loader->layer1->layerN->driver
		//"Creating an instance initializes the loader. The loader also loads and initializes the layers and the low-level graphics driver, usually 
		//provided by the vendor of the GPU hardware.
		//Layers are commonly used for validation, which is the error checking that would normally be performed by the driver."
		//This allows the drivers to be more light weight.
		VkInstance m_vkInstance;

		//vkGuide: VkPhysicalDevice : "A GPU. Used to query physical GPU details, like features, capabilities, memory size, etc."
		VkPhysicalDevice m_physDev;
		VkPhysicalDeviceProperties m_physDevProperties;

		//vkGuide: VkDevice : "The “logical” GPU context that you actually execute things on."
		VkDevice m_logDev;

		PFN_vkCmdDrawMeshTasksEXT m_vkCmdDrawMeshTasksEXT;

		static void createSemaphores( const VkDevice& logDev, std::vector<FrameData>& frameDataStructs, size_t currentFrameNumber );


		//the actual VkSwapchainKHR object is a bit confusing: obviously, conceptually the swapchain is a queue of image views
		//that you can draw to, but the actual swapchain object isn't used all that much: we keep the swapchain image views
		// themselves in m_swapchainImages and use them directly most of the time. Instead, you really just use the swapchain
		//object during the creation of those image views, and then you use it to get at the next available image view
		//at the start of draw()
		VkSwapchainKHR m_swapchain;
		VkSwapchainCreateInfoKHR m_swapchainInfo;
		//vkGuide: "A VkImage is a handle to the actual image object to use as texture or to render into. A VkImageView is a 
		//wrapper for that image. It allows to do things like swap the colors."
		//std::vector<VkImage>m_swapchainImages;
		//std::vector<VkImageView>m_swapchainImageViews;

		std::vector<ImageResource> m_swapchainImageResources;

		//surface used mainly in construction of swap chain, where you use it to get the supported formats (eg. BGRA), present
		//modes etc. 
		VkSurfaceKHR m_surface;
		uint32_t m_screenWidth;
		uint32_t m_screenHeight;
		VkSurfaceFormatKHR m_surfaceFormat;


		VkQueue m_graphicsQueue;
		//needs to be uint32_t for Vulkan
		uint32_t m_graphicsFamilyIndex;

		//If one command buffer's in use by the gpu as it draws to one frame, you can't rerecord that command buffer until it's done.
		//So we need a separate buffer (and synchronization primitives) for each frame
		std::vector<FrameData> m_frameDataStructs{ FRAME_OVERLAP };


		uint64_t m_currentFrameNumber;


		VkDebugUtilsMessengerEXT m_debugMessenger;

		//It is necessary for the timeline semaphore to keep track of the completed frame count, rather than the 'last completed frame'.
		// Otherwise, if the timeline semaphore was updated to tell us 'the last completed frame number was x', instead of 'x frames have been completed', then we'd have a bug: the lowest value that the semaphor can be set to is 0, so it would always tell us that at least frame 0 had been completed, when this might not be the case.
		//VkSemaphore m_commandBufferSemaphore_completedFrameCount;

		VmaAllocator m_vmaAllocator;
		//buffers for the vertex and index buffers, and for the uniform buffer objects (the textures are images rather than
		//plain buffers)
		std::vector<AllocatedBuffer> m_allocatedBuffers;



		static constexpr uint32_t DESCRIPTOR_GROUP_COUNT = 2;

		std::shared_ptr<DescriptorSlot> m_cameraBufferDescriptorSlot;
		std::shared_ptr<DescriptorSlot> m_textureArrayDescriptorSlot;
		std::shared_ptr<DescriptorSlot> m_spriteBufferDescriptorSlot;
		std::shared_ptr<DescriptorSlot> m_preprocessedImageBufferDescriptorSlot;


		//ToDo maybe this should just be an index, because it's stored in m_allocatedBuffers anyway, but bear with me for now
		//Don't clean this up: it's cleaned up when the vector of AllocatedBuffers is destroyed
		AllocatedBuffer m_cameraBuffer;
		
		
		//AllocatedBuffer m_spriteBuffer;
		//AllocatedBuffer m_spriteStagingBuffer;


		VkDescriptorPool m_descriptorPool;

		//No need to clean this up: automatically destroyed when the pool is cleaned up
		//VkDescriptorSet m_globalDescriptorSet;

		/*CrayDescriptorSet m_globalDescriptorSet;

		CrayDescriptorSet m_stagingImagesDescriptorSet;*/

		DescriptorSuperset m_descriptorSuperset;

		//to do : rename this!
		std::shared_ptr<DescriptorSet> m_globalDescriptorSet;
		std::shared_ptr<DescriptorSet> m_stagingImagesDescriptorSet;
		std::shared_ptr<DescriptorSet> m_textureDescriptorSet;
		std::shared_ptr<DescriptorSet> m_spriteBufferDescriptorSet;



		std::vector<uint16_t> m_indicesForIndexBuffer;

		AllocatedBuffer m_quadIndexBuffer;


		std::vector<ImageResource> m_textureHandles;
		VkSampler m_textureSampler;
		std::unordered_map<std::string, size_t> m_textureIDMap;


		//the callback function we'll give to the Vulkan debug messenger
		//VKAPI_ATTR is about visiblity and linkage, is important if you're turning this into a dll
		//VKAPI_CALL on Windows becomes __stdcall
		static VKAPI_ATTR VkBool32 VKAPI_CALL validationDebugCallback(
			// How important the message is (verbose, info, warning, error)
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			// What kind of message it is (general, validation, performance)
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			// The actual message data
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			// Optional user data passed through from messenger creation
			void* pUserData );

		void setUpVulkanDebugMessenger();

		static void setUpCommandBufferWithDesiredSettings( VkCommandBuffer& commandBuffer, const VkExtent2D& swapchainImageExtent, float screenWidth, float screenHeight );




		static void bindDescriptorSuperset( const DescriptorSuperset& superset, const Pipeline& pipeline, const VkCommandBuffer& commandBuffer );




		static void sumbitCommandBuffer( const VkQueue& graphicsQueue, FrameData& frameData );



		glm::vec2 m_cameraPosition;

		static int createVulkanInstance( VkInstance& vkInstance );
		static void createSurface( const HWND& winHandle, const VkInstance& vkInstance, VkSurfaceKHR& surface );
		void initPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain( HWND winHandle );
		void cleanUp();

		void setScreenExtent( const uint32_t width, const uint32_t height );


		void createCommandPool( VkCommandPool& commandPool );

		static void setUpGraphicsQueueCommandPoolsAndBuffers( const VkDevice& logDev, const size_t& graphicsFamilyIndex, VkQueue& graphicsQueue, std::vector<FrameData>& frameDataStructs );

		void loadShaderModule( const char* filePath, VkShaderModule* pOutShaderModule );
		void createPipelineLayout( VkPipelineLayout& pipelineLayout, const VkPushConstantRange& pushConstantRange );
		void createPipeline( Pipeline& pipeline, const VkFormat& destinationImageFormat, float lineThickness = 1.f );

		void mapMemory( AllocatedBuffer dstBuffer, void* data, size_t size, size_t offsetWithinDestination = 0 );

		void createCameraBufferAndUpdateDescriptorSet();

		void createStorageImagesAndUpdateDescriptorSet();

		void setUpPipelines();

		static void setUpAllocator( const VkInstance& vulkanInstance, const VkDevice& logDev, const VkPhysicalDevice& physDev, VmaAllocator& allocator );


		void setUpIndexBuffer( AllocatedBuffer& allocatedBuffer, std::vector<uint16_t>& indices );


	
		

		uint32_t findMemTypeIndex( VkMemoryPropertyFlags wantedProperties, uint32_t memTypeBits );

		//deprecated: we're moving to using VkMemoryPropertyFlags instead of a VmaMemoryUsage (Vma has moved on to getting you to use VkMemoryPropertyFlags and always just passing in VMA_MEMORY_USAGE_AUTO as the VmaMemoryUsage)
		void createVmaBuffer( VkDeviceSize deviceSize, VkBufferUsageFlags buffUseFlags, AllocatedBuffer& allocatedBuffer, VmaMemoryUsage usage );

		void createVmaBuffer( VkDeviceSize deviceSize, VkBufferUsageFlags buffUseFlags, AllocatedBuffer& allocatedBuffer, VkMemoryPropertyFlags memoryPropertyFlags, VmaAllocationCreateFlags allocationFlags = {} );

		void createImage( uint32_t width, uint32_t height, VkFormat& format, VkImageTiling tiling, VkImageUsageFlags usage,
			VkMemoryPropertyFlags memoryProperties, VkImage& image, VmaAllocation& imageAllocation );

		VkCommandBuffer beginTempComBuffer();
		void useUpTempComBuffer( VkCommandBuffer tempComBuffer );

		void copyBuffer( VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size );

		//ToDo: this can be made more general, into an 'updateGPUBuffer' function instead

		static void setUpDescriptorPool( const VkDevice& logDev, const DescriptorSuperset& superset, VkDescriptorPool& descriptorPool );

		static void setUpDescriptorSetLayout( const VkDevice& logDev, DescriptorSet& descriptorSet );

		static void allocateToDescriptorSet( const VkDevice& logDev, const VkDescriptorPool& descriptorPool, VkDescriptorSetLayout& descriptorSetLayout, VkDescriptorSet& descriptorSet );

		static void allocateToDescriptorSets( const VkDevice& logDev, const VkDescriptorPool& descriptorPool, DescriptorSuperset& superSet );

		void setUpDescriptors();

		void setUpDepthImages( uint32_t width, uint32_t height, bool useForSampling );

		void setUpAllocatorThenResourcesAndDescriptorSets();


		ImageResource loadTexture_fileToGPU( const char* fileName );

		void transitionImageLayout( VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout );

		void copyBufferToImage( VkBuffer buffer, VkImage image, uint32_t width, uint32_t height );

		VkImageView createImageView( VkImage image, VkFormat format, VkImageAspectFlags aspectFlags );

		void updateTextureDescriptors( std::vector<ImageResource>& nexTextureHandles );


		void createTextureSampler();


		FrameData& getCurrentFrame();

		void cleanUpSwapChain();

		void cleanUpPreprocessingImagesAndTheirDepthBuffers();

		void loadTexturesAndAddToTextureBinding( const std::vector<const char*>& textureNames );

		void recreateSwapChain( HWND winHandle );

	public:

		Renderer() = default;
		Renderer( const Renderer& other ) = delete;
		Renderer& operator=( const Renderer& other ) = delete;

		virtual ~Renderer();

		int init( HWND winHandle, glm::uvec2 screenExtent, const std::unordered_map < std::string, std::string>& editorSettings );

		size_t addTextureIfNew( const char* textureName );
		ImageResource& getTextureHandle( size_t textureIndex );


		//to do: in the future we'll store the Renderpasses in a map and search by name etc. but for now we can just hardcode this
		//also, should we rename 'Renderpass' to 'AttachmentGroup' or something?
		AttachmentGroup getUiRenderpassInfo() const;


		void startDrawFrame();
		void endDrawFrame();


		static void beginRenderpass( std::vector<const ImageResourceUsage*>& imageResourceUsages,std::vector< ImageResource*>& imageResources, const VkCommandBuffer& commandBuffer );


		void beginRenderpass_main();
		void beginRenderpass_postprocessing();

		void endRenderPass();

		static void insertImageLayoutTransition( ImageResource& imageResource, const ImageResourceUsage& imageResourceUsage, VkCommandBuffer commandBuffer );

		static void updateImageResourceState( const ImageResourceUsage& imageUsage, ImageResource& imageResource );

		static void updateAttachmentImages( std::vector<const ImageResource*>& imageResources,  std::vector<const ImageResourceUsage*>& imageResourceUsages, const VkCommandBuffer& commandBuffer );

		static void updateDescriptorSlot( const VkDevice& logicalDevice, const DescriptorSlot& slot, const VkBuffer& buffer );

		void resetImageResources();

		static constexpr VkPipelineDepthStencilStateCreateInfo DEPTH_STENCIL_DEFAULT_SETTINGS =
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
			.pNext= nullptr,
			.flags = {},
			.depthTestEnable = true,
			.depthWriteEnable = true,
			.depthCompareOp = VK_COMPARE_OP_LESS,
			.depthBoundsTestEnable = VK_FALSE,
			.stencilTestEnable = VK_FALSE,
			.front = {},
			.back = {},
			.minDepthBounds = 0.0f,
			.maxDepthBounds = 1.f
		};

		template<typename T>
		void copyViaStagingBuffer( std::vector<T> vector, AllocatedBuffer& stagingBuffer, AllocatedBuffer& destinationBuffer )
		{
			size_t copySize = vector.size() * sizeof( T );
			mapMemory( stagingBuffer, vector.data(), copySize );
			copyBuffer( stagingBuffer.buffer, destinationBuffer.buffer, copySize );
		}

		template<typename T>
		void draw( Pipeline& pipeline, std::vector<T>& pushConstants, uint32_t workGroupCount =1)
		{
			//get correct command buffer
			VkCommandBuffer& commandBuffer = getCurrentFrame().mainCommandBuffer;
			//bind the pipeline to the graphics bind point
			vkCmdBindPipeline( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.m_pipeline );
			
			//I'd like to move this to 'startDrawFrame', but vkCmdBindDescriptorSets uses a specific pipeline layout. It might be that it would work out, given that all the pipelines use the same descriptor superset, but it doesn't seem worth potentially doing something weird to get rid of, say, 10 descriptor set rebinds (max) per frame, so let's just keep it here.

			//Oh wait the Pipeline object itself should say what superset it wants...
			m_cameraBufferDescriptorSlot->currentIndex = m_currentFrameNumber % FRAME_OVERLAP;
			bindDescriptorSuperset(m_descriptorSuperset, pipeline, commandBuffer );

			VkPipelineLayout& pipelineLayout = pipeline.m_pipelineLayout;

			CRAYON_ASSERT( pipeline.m_shaderType == ShaderType::MESH );
			for ( const auto& pushConstant : pushConstants )
			{
				vkCmdPushConstants( commandBuffer, pipelineLayout, pipeline.m_pushConstantShaderStageFlags, 0, sizeof( T ), &pushConstant );

				m_vkCmdDrawMeshTasksEXT( commandBuffer, workGroupCount, 1, 1 );
			}

		}

		VkFormat getSwapchainImageFormat();

		void drawGameSprites( std::vector<Sprite>& spriteVector );
		void drawUISprites( std::vector<Sprite>& spriteVector );
		void drawSolidShapes( std::vector<Rect>& rectVector );
		void drawCircles( std::vector<Rect>& rectVector );
		void drawColourCorrection();

		size_t getScreenWidth() const;
		size_t getScreenHeight() const;
		void recreateSwapChainAndUpdateDependencies( HWND winHandle );

		void setUpPreprocessImages(VmaAllocator& allocator);
		void setCameraPosition( float x, float y );
		void setCameraPosition( glm::vec2 newPos );
		float getCameraX() const;
		glm::vec2 getCameraPosition2D() const;
		float getCameraY() const;
		void updateCameraPosition();

		void initPipeline( Pipeline& pipeline, const std::string& name, ShaderType shaderType, const VkDevice& logDev, VkPushConstantRange pushConstantRange, VkFormat targetFormat, bool usesDepthBuffer );

		MVP getCameraAsMvp() const;
		glm::vec2 getScreenToWorld( glm::vec2 screenspaceVector ) const;
		glm::vec2 getPixelsToNdcs( glm::ivec2 pixelScreenCoord ) const;


		VkInstance getInstance() { return m_vkInstance; }
		VkPhysicalDevice getPhysicalDevice() { return m_physDev; }
		VkDevice getDevice() { return m_logDev; }

		VkQueue getGraphicsQueue() { return m_graphicsQueue; }
		size_t getGraphicsQueueFamilyIndex() { return m_graphicsFamilyIndex; }
		VkDescriptorPool getDescriptorPool() { return m_descriptorPool; }
		size_t getSwapChainImageCount() { return m_swapchainImageResources.size(); }
		VkCommandBuffer& getCurrentCommandBuffer() { return getCurrentFrame().mainCommandBuffer; }


		//PIPELINE STUFF
		std::vector<Pipeline*> m_pipelines;
		Pipeline m_spritePipeline;
		Pipeline m_spriteBatchPipeline;
		Pipeline m_solidShapePipeline;
		Pipeline m_uiSpritePipeline;
		Pipeline m_linePipeline;
		Pipeline m_circlePipeline;
		Pipeline m_colorCorrectionPipeline;

		//hacky: made this public just for test
		FastGpuBuffer m_spriteBuffer;

	};


}