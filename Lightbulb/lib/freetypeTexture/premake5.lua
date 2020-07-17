--freetypeTexture dependency
project "freetypeTexture"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin/" .. outputDir .. "/%{prj.name}")

    files
    {
        "include/ftgl/*.h",
        "src/ftgl/*.c",
        "lib/freetype/include"
    }

    includedirs
    {
        "include",
        "lib/freetype/include"
    }

    links
    {
        "lib/freetype/objs/freetype.lib"
    }

    filter "system:windows"
        systemversion "latest"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

