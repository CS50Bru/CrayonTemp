#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#include"Core.h"


namespace Crayon
{
	namespace fs = std::filesystem;
	class ShaderManager
	{

	public:

		static bool updateHeader( std::string& content, const fs::path& filepath );
		static bool updateDescriptorInfo( std::string& content, const fs::path& filepath );
		static bool addBoilerplatToShader( const fs::path& filepath );
		static void injectBoilerplate( const std::string& shaderDir );

		static void compileSpirV( const std::string& shaderCodeDirectoryPath, const std::string& spirvOutputDirectoryPath, const std::string& targetVulkanVersion, const std::string& targetSpirvVersion, bool forceCompileAll = true );
	};

}