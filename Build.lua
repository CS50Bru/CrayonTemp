--workspace is basically the .sln. There are some things that you can set here for the whole workspace like the architecture,
--but a lot of other stuff, like the language, has to be set per project because you can mix together projects written in separate languages
--such as having a C# App use a C++ Core library etc.

--workspace "Blah" is actually a FUNCTION CALL, as bizarre as that might seem: when you're just passing in a single argument you don't
--need parentheses.

--what we're doing here is announcing a workspace and entering it at the same time: we're saying, "Hey, in the CrayonWorkSpace we have...".
--we're NOT creating a variable here: 
workspace "CrayonWorkspace"

-- this step (defining the architecture) is so important: the linker errors that you get if you mess it up are really confusing
    architecture "x64"
    configurations{"Debug", "Release"}

local vkSDK= os.getenv("VULKAN_SDK")



project "CrayonEngineGameCombined"
    location "CrayonEngineGameCombined"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}"
    staticruntime "off"
    files {
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp",
        "%{prj.location}/**.c",
        "%{prj.location}/**.hpp",
        "%{prj.location}/**.h",
        "%{prj.location}/**.hpp"
    }

    --Windows: An absolute path starts with a drive letter and colon (C:/) or a network share (\\server\share).
    includedirs{ vkSDK.."/Include","%{prj.location}", "%{prj.location}/Crayon", "%{prj.location}/Crayon/Core",
    "%{prj.location}/Crayon/WindowAndInput", "%{prj.location}/Crayon/Core/LoggingAndProfiling", "%{prj.location}/Crayon/Core/CoreTypes", "%{prj.location}/Crayon/Core/Reflection",
    "%{prj.location}/Crayon/Core/Events", 
    "%{prj.location}/Crayon/Components", "%{prj.location}/Crayon/Systems", "%{prj.location}/Crayon/ECS", "%{prj.location}/Game/Components",
    "%{prj.location}/Game/Systems", "%{prj.location}/Crayon/Subsystems/Rendering",
    "%{prj.location}/Crayon/Subsystems/ECS",  "%{prj.location}/Crayon/Subsystems", "%{prj.location}/Crayon/ComponentsAndSystems", 
    "%{prj.location}/Crayon/ComponentsAndSystems/Components", "%{prj.location}/Crayon/ComponentsAndSystems/Systems", "External/yaml_cpp/include",}

    --"libdirs" sets up the directories to search for the libraries.
    --"links" lists the specific libraries to link against.
    libdirs{vkSDK.."/Lib"}

    --NB Premake adds the .lib extension for you. So, it has a list of places to look for .lib files thanks to libdirs{...},
    --and once it's got that list it automatically starts looking for "vulkan-1.lib"
    links{"vulkan-1", "yaml_cpp"}

    defines{"YAML_CPP_STATIC_DEFINE", "EDITOR"}

    filter "system:windows"
        defines {"WINDOWS"}

    filter "configurations:debug"
        defines {"DEBUG", "VULKAN_DEBUG"}
        runtime "Debug"

    filter "configurations:release"
        runtime "Release"

    


    --this is generally where you'll put some {COPY} commands to copy any necessary .dlls into whatever directory you're putting
    --your .exes in. The libdirs stuff just links the .lib files: it doesn't sort out the .dlls for you.
    postbuildcommands 
    {

    }

project "yaml_cpp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"
    location "External/yaml_cpp"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}"
    staticruntime "off"

    files { "%{prj.location}/src/**.h", "%{prj.location}/src/**.cpp" }
    includedirs { "%{prj.location}/include" }

    defines { "YAML_CPP_STATIC_DEFINE" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"