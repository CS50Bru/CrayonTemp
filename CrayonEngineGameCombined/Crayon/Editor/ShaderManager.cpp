#include "ShaderManager.h"

namespace Crayon
{

	//apparently, according to Grok, these \ns will be automatically converted to \r\n when added to a stream in a Windows build, if you're writing to the stream in write mode, as opposed to more manually in binary mode.
	static constexpr std::string_view HEADER_START = "// STANDARD HEADER BEGINS\n";
	static constexpr std::string_view HEADER_END = "// STANDARD HEADER ENDS\n";

	static constexpr std::string_view DESCRIPTOR_INFO_START = "//DESCRIPTOR INFORMATION BEGINS";
	static constexpr std::string_view DESCRIPTOR_INFO_END = "//DESCRIPTOR INFORMATION ENDS";

	static const std::string FRAG_HEADER =
		"// STANDARD HEADER BEGINS\n"
		"#version 450\n"
		"#extension GL_EXT_nonuniform_qualifier : enable\n"
		"// STANDARD HEADER ENDS\n";

	static const std::string MESH_HEADER =
		"// STANDARD HEADER BEGINS\n"
		"#version 450\n"
		"#extension GL_EXT_mesh_shader : require\n"
		"#extension GL_EXT_nonuniform_qualifier : enable\n"
		"#define CRAYON_MAX_VERTICES_PER_MESH_SHADER_WORKGROUP 256\n"
		"#define CRAYON_MAX_PRIMITIVES_PER_MESH_SHADER_WORKGROUP 256\n"
		"// STANDARD HEADER ENDS\n";

	static const std::string STANDARD_DESCRIPTOR_INFO = R"(//DESCRIPTOR INFORMATION BEGINS
// Define our DescriptorSet inputs
layout( set = 0, binding = 0, std140 ) uniform UniformBufferObject
{
	mat4 model;
	mat4 view;
	mat4 proj;
} ubo;

layout( set = 1, binding = 0 ) uniform sampler2D texSampler[];

layout( set = 2, binding = 0, rgba8 ) readonly uniform image2D stagingImages[];


struct Sprite {
    vec2 offset;       // Position offset in model space
    vec2 origin;       // Texture coordinate origin
    vec2 extent;       // Texture coordinate extent
    vec2 scale;        // Scaling factor for the sprite
    uint textureID;    // Index into the texture sampler array
    float rotation;    // Rotation angle in radians
};

layout( set = 3, binding =0, std140) readonly buffer SpriteBuffer {Sprite sprites[];} spriteBuffer;


//DESCRIPTOR INFORMATION ENDS)";


	bool ShaderManager::updateHeader( std::string& content, const fs::path& filepath )
	{
		size_t startPos = content.find( HEADER_START );
		size_t endPos = content.find( HEADER_END );

		if ( startPos == std::string::npos || endPos == std::string::npos || endPos <= startPos )
		{
			std::cerr << "Could not find header start in " << filepath << std::endl;
			return false;
		}


		endPos += HEADER_END.length();

		std::string newHeader = filepath.extension() == ".mesh" ? MESH_HEADER : FRAG_HEADER;

		std::string updatedContent = content.substr( 0, startPos ) + newHeader + content.substr( endPos );

		content = std::move( updatedContent );
		return true;
	}

	bool ShaderManager::updateDescriptorInfo( std::string& content, const fs::path& filepath )
	{
		size_t startPos = content.find( DESCRIPTOR_INFO_START );
		size_t endPos = content.find( DESCRIPTOR_INFO_END );

		if ( startPos == std::string::npos || endPos == std::string::npos || startPos >= endPos )
		{
			std::cerr << "Could not find descriptor info start in " << filepath << std::endl;
			return false;
		}

		endPos += DESCRIPTOR_INFO_END.length();

		std::string updatedContent = content.substr( 0, startPos ) + STANDARD_DESCRIPTOR_INFO + content.substr( endPos );

		content = std::move( updatedContent );

		return true;
	}

	bool ShaderManager::addBoilerplatToShader( const fs::path& filepath )
	{
		{
			//read the file into a string called CONTENT
			//std::ios::in is a flag you pass to an std::ifstream (input file stream) when opening a file, telling it you want to read from the file
			std::ifstream inFileStream( filepath, std::ios::in );
			if ( !inFileStream )
			{
				std::cerr << "Error: Could not open " << filepath << std::endl;
				return false;
			}
			//std::string has a constructor that takes a pair of iterators (a range) and builds the string by copying all data between them.
			std::string content{ std::istreambuf_iterator<char>( inFileStream ), std::istreambuf_iterator<char>() };

			inFileStream.close();


			updateHeader( content, filepath );

			updateDescriptorInfo( content, filepath );


			std::ofstream outFile( filepath, std::ios::out | std::ios::trunc );

			if ( !outFile )
			{
				std::cerr << "Could not write to file: " << filepath << std::endl;
				return false;
			}

			outFile << content;
			outFile.close();

			std::cout << "Updated " << filepath << std::endl;

			return true;
		}
	}

	

	void ShaderManager::compileSpirV( const std::string& shaderCodeDirectoryPath, const std::string& spirvDirectoryPath, const std::string& targetVulkanVersion, const std::string& targetSpirvVersion, bool forceCompileAll)
	{
		//see if the Vulkan SDK is installed
		const char* vulkanSdk = std::getenv( "VULKAN_SDK" );

		CRAYON_ASSERT( vulkanSdk!= nullptr && "Could not find VULKAN_SDK environment variable. Is the Vulkan SDK installed? If so, has the VULKAN_SDK environment variable not been created?");

		std::cout << "Vulkan SDK found" << std::endl;

		if ( !fs::exists( spirvDirectoryPath ) )
		{
			fs::create_directories( spirvDirectoryPath );
		}
		
		//get the path to the glslc shader-code-to-spirv compiler within the Vulkan SDK directory
		std::string glslc = vulkanSdk + std::string("/Bin/glslc.exe");

		CRAYON_ASSERT( fs::exists( glslc ) && "Could not find glslc.exe. If you've reached this point then VULKAN_SDK was probably found, but the shader compiler within it was not. Check wherever the Vulkan SDK is installed for /Bin/glslc.exe");
		std::cout << "glslc.exe shader compiler found" << std::endl << "Compiling shaders into SPIR V" << std::endl;

		for ( const auto& entry : std::filesystem::directory_iterator( shaderCodeDirectoryPath ) )
		{
			//check that this is a file as opposed to a directory, and that we can get its name
			if ( !entry.is_regular_file() )
			{
				continue;
			}
			const std::string entryPath = entry.path().string();
			CRAYON_ASSERT( !entryPath.empty() && "Could not get file name");

			//check that it has an actual extension, and if it does make sure that the extension is of a type we're expecting
			std::string extension = entry.path().extension().string();

			CRAYON_ASSERT( !extension.empty() && (extension.size()>1) && "Could not read file extension");
			extension.erase( 0, 1 );

			if ( !(extension == "vert" || extension == "frag" || extension == "mesh") )
			{
				std::cout << entryPath + " did not have expected extension (was not a type of shader)" << std::endl;
				continue;
			}

			//Now that we know we're actually dealing with a shader file, we need to check whether we already have the latest spirv code for it


			const std::string outputFilePath =spirvDirectoryPath + "/" + entry.path().stem().string() + "_" + extension + ".spv";
			
			//if a matching .spv exists, check if it's up-to-date with the source code. If it is don't bother compiling it
			if ( fs::exists( outputFilePath ) )
			{
				auto shaderSourceLastWriteTime = fs::last_write_time( entry );
				auto spirVFileLastWriteTime = fs::last_write_time(outputFilePath);

				if ( (spirVFileLastWriteTime > shaderSourceLastWriteTime)  && !forceCompileAll )
				{
					std::cout << outputFilePath << " is already up to date, moving on to next shader source file" << std::endl;
					continue;
				}
			}

			//now do the actual compiling
			std::cout << "Compiling " + entryPath << " as " << outputFilePath << std::endl;

			addBoilerplatToShader( entryPath );
			const std::string command = glslc + " --target-env=" + targetVulkanVersion +" --target-spv=" + targetSpirvVersion + " " + entry.path().string() + " -o " + outputFilePath;


			int compilationResult = std::system( command.data() );

			CRAYON_ASSERT( compilationResult == 0 && "Shader Compilation failed");

			std::cout << outputFilePath + " successfully compiled" << std::endl;

		}

	}

}
