#pragma once
#include"Core.h"

//Ties together VkPipeline and a VkPipelineLayout (and in doing so assumes that every VkPipeline has its own, unique layout).
//maybe sometimes you'd want to share layouts but I haven't run into this yet. In that case you could just have a shared pointer to the layout so not a big deal?
//Same story with the shader modules: for now it's easier to just treat them as being automatically unique to the Pipeline.

//Creating pipelines in Crayon:

//It's actually pretty painless. Creating RESOURCES is difficult, and making sure the bindings match up between the cpp code and the shader code is difficult, but the pipelines themselves?
//The biggest part of it is the PipelineLayout, and that's mostly made up of describing the descriptor sets you're going to bind to the shaders. Given that we only have a single, 'global' descriptor superset, that's easy to do.

namespace Crayon
{

	enum class ShaderType
	{
		UNSPECIFIED = 0,
		VERTEX=1,
		MESH=2
	};


	class Pipeline
	{
	public:
		Pipeline() {};
		Pipeline( const Pipeline& other ) = delete;
		Pipeline& operator=( const Pipeline& other ) = delete;

		Pipeline( Pipeline&& other ) noexcept
		{
			m_logDev =other.m_logDev;
			m_name = std::move( other.m_name );
			m_inputAssemblyInfo = other.m_inputAssemblyInfo;
			m_pushConstantRange = other.m_pushConstantRange;
			m_vertShadMod = other.m_vertShadMod;
			other.m_vertShadMod = VK_NULL_HANDLE;
			m_fragShadMod = other.m_fragShadMod;
			other.m_fragShadMod = VK_NULL_HANDLE;
			m_pipelineLayout = other.m_pipelineLayout;
			other.m_pipelineLayout = VK_NULL_HANDLE;
			m_pipeline = other.m_pipeline;
			other.m_pipeline = VK_NULL_HANDLE;
			m_initialized = other.m_initialized;
			m_cleanedUp = other.m_cleanedUp;
			other.m_cleanedUp = true;
		}

		void cleanup()
		{
			//if we're cleaning this up after the logical device has been destroyed then mistakes have been made
			CRAYON_ASSERT( m_logDev != VK_NULL_HANDLE );
			if ( m_cleanedUp|| m_logDev==VK_NULL_HANDLE )
			{
				return;
			}
			m_cleanedUp = true;
			if ( m_pipeline != VK_NULL_HANDLE )
			{
				vkDestroyPipeline( m_logDev, m_pipeline, nullptr );
				m_pipeline = VK_NULL_HANDLE;
			}
			if ( m_pipelineLayout != VK_NULL_HANDLE )
			{
				vkDestroyPipelineLayout( m_logDev, m_pipelineLayout, nullptr );
				m_pipelineLayout = VK_NULL_HANDLE;
			}
			if ( m_vertShadMod != VK_NULL_HANDLE )
			{
				vkDestroyShaderModule( m_logDev, m_vertShadMod, nullptr );
				m_vertShadMod = VK_NULL_HANDLE;
			}
			if ( m_fragShadMod != VK_NULL_HANDLE )
			{
				vkDestroyShaderModule( m_logDev, m_fragShadMod, nullptr );
				m_fragShadMod = VK_NULL_HANDLE;
			}
		}


		~Pipeline()
		{
			if ( !m_cleanedUp )
			{
				cleanup();
			}
		}


		//not owned
		VkDevice m_logDev;

		std::string m_name = "UnnamedPipeline";
		
		
		ShaderType m_shaderType = ShaderType::UNSPECIFIED;
		VkPipelineInputAssemblyStateCreateInfo m_inputAssemblyInfo = {};
		VkPushConstantRange m_pushConstantRange{};
		VkDescriptorSetLayout m_descriptorSetLayout{};
		VkShaderStageFlags m_pushConstantShaderStageFlags{};
		VkShaderModule m_vertShadMod=VK_NULL_HANDLE;
		VkShaderModule m_meshShadMod = VK_NULL_HANDLE;
		VkShaderModule m_fragShadMod= VK_NULL_HANDLE;
		VkPipelineLayout m_pipelineLayout= VK_NULL_HANDLE;
		VkPipeline m_pipeline = VK_NULL_HANDLE;
		bool m_initialized = false;
		bool m_cleanedUp = false;
		bool m_usesDepthBuffer = false;
	};


}