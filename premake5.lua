workspace "Raytracer"
    --x64
    architecture "x86_64"
    startproject "Raytracer"
    
    --confingurations wanted
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    --compiler flags
    flags
    {
        "MultiProcessorCompile" --get vs to use multiple threads when compiling
    }

    -- Generic output dir name for each project
    outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- library includes relative to root
    libIncDir = {}
    libIncDir["glad"] = "Raytracer/lib/glad/include"
    libIncDir["stb_image"] = "Raytracer/lib/stb_image/include"
    libIncDir["glm"] = "Raytracer/lib/glm/include"
    libIncDir["glfw"] = "Raytracer/lib/glfw/include"

    -- project src/lib locations relative to project
    projectSrc = "%{prj.name}/src"
    projectLib = "%{prj.name}/lib"

    -- library premake5 files to run/build
    group "External Dependencies"
        include "Raytracer/lib/glad"
        include "Raytracer/lib/stb_image"
        include "Raytracer/lib/glm"
        include "Raytracer/lib/glfw"
    group ""

    project "Raytracer"
        location "Raytracer" --where is it relative to root
        kind "ConsoleApp" --static (StaticLib), dll (SharedLib), exe (ConsoleApp, WindowedApp)
	    language "C++" --language
	    cppdialect "C++17" --cpp standard
        staticruntime "on" --sets runtime library to multitreaded (Visual studio only)
        
        targetdir ("bin/" .. outputDir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

        --precompiled header
        pchheader "rtpch.h"
        pchsource "Raytracer/src/rtpch.cpp"

        --source files
        files
        {
            projectSrc .. "/**.h",
            projectSrc .. "/**.cpp",
        }

        --any defines
        defines
        {
            
        }

        --include dirs
        includedirs
        {
            projectSrc,
            "%{libIncDir.glad}",
            "%{libIncDir.stb_image}",
            "%{libIncDir.glm}",
            "%{libIncDir.glfw}"
        }

        --libs to link against
        links
        {
            "opengl32.lib",
            "glad",
            "glfw"
        }

        --everything below is windows specific
        filter "system:windows"
            systemversion "latest"
            defines
            {
                "PLATFORM_WINDOWS"
            }
        
        --debug settings
        filter "configurations:Debug"
            defines "CONFIG_DEBUG"
            runtime "Debug"
            symbols "on"
        
        --release settings
        filter "configurations:Release"
            defines "CONFIG_RELEASE"
            runtime "Release"
            optimize "on"

        --dist settings
        filter "configurations:Dist"
            defines "CONFIG_RELEASE"
            runtime "Release"
            optimize "on"

