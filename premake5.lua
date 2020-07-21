workspace "Light"
    --x64
    architecture "x86_64"
    startproject "Laser"

    --API_OPENGL, API_DX11, etc
    rendererApi = "API_OPENGL"
    
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
    libIncDir["glad"] = "Lightbulb/lib/glad/include"
    libIncDir["stb_image"] = "Lightbulb/lib/stb_image/include"
    libIncDir["glm"] = "Lightbulb/lib/glm/include"
    libIncDir["glfw"] = "Lightbulb/lib/glfw/include"
    libIncDir["spdlog"] = "Lightbulb/lib/spdlog/include"
    libIncDir["freetypeTexture"] = "Lightbulb/lib/freetypeTexture/include"
    libIncDir["imgui"] = "Lightbulb/lib/imgui/include"
    libIncDir["imgui_backend"] = "Lightbulb/lib/imgui/examples"

    -- project src/lib locations relative to project
    projectSrc = "%{prj.name}/src"
    projectLib = "%{prj.name}/lib"

    -- library premake5 files to run/build
    group "External Dependencies"
        include "Lightbulb/lib/glad"
        include "Lightbulb/lib/stb_image"
        include "Lightbulb/lib/glm"
        include "Lightbulb/lib/glfw"
        include "Lightbulb/lib/spdlog"
        include "Lightbulb/lib/freetypeTexture"
        include "Lightbulb/lib/imgui"
    group ""

    project "Lightbulb"
        location "Lightbulb" --where is it relative to root
        kind "StaticLib" --static (StaticLib), dll (SharedLib), exe (ConsoleApp, WindowedApp)
	    language "C++" --language
	    cppdialect "C++17" --cpp standard
        staticruntime "on" --sets runtime library to multitreaded (Visual studio only)
        
        targetdir ("bin/" .. outputDir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

        --precompiled header
        pchheader "lbpch.h"
        pchsource "Lightbulb/src/lbpch.cpp"

        --source files
        files
        {
            projectSrc .. "/**.h",
            projectSrc .. "/**.cpp",
        }

        --any defines
        defines
        {
            rendererApi,
        }

        --include dirs
        includedirs
        {
            projectSrc,
            "%{libIncDir.glad}",
            "%{libIncDir.stb_image}",
            "%{libIncDir.glm}",
            "%{libIncDir.glfw}",
            "%{libIncDir.spdlog}",
            "%{libIncDir.freetypeTexture}",
            "%{libIncDir.imgui}",
            "%{libIncDir.imgui_backend}"
        }

        --libs to link against
        links
        {
            "opengl32.lib",
            "glad",
            "glfw",
            "spdlog",
            "freetypeTexture",
            "imgui"
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
            defines "CONFIG_DIST"
            runtime "Release"
            optimize "on"

    project "Laser"
        location "Laser"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir ("bin/" .. outputDir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

        files
        {
            projectSrc .. "/**.h",
            projectSrc .. "/**.cpp",
        }

        includedirs
        {
            "Lightbulb/src",
            "%{libIncDir.glm}",
            "%{libIncDir.spdlog}"
        }

        defines
        {
            rendererApi,
        }

        links
        {
            "Lightbulb",
            "spdlog"
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "PLATFORM_WINDOWS"
            }
		
        filter "configurations:Debug"
            defines "CONFIG_DEBUG"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "CONFIG_RELEASE"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "CONFIG_DIST"
            runtime "Release"
            optimize "on"