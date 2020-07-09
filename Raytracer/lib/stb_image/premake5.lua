--stb image dependency
project "stb_image"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin/" .. outputDir .. "/%{prj.name}")

    files
    {
        "include/stb/stb_image.h"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

