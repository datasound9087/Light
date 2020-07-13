--glm dependency
project "glm"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin/" .. outputDir .. "/%{prj.name}")

    files
    {
        "include/glm/*.hpp",
        "include/glm/*.inl"
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

