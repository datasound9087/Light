--imgui dependency
project "imgui"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin/" .. outputDir .. "/%{prj.name}")

    files
    {
        "include/imgui/*.h",
        "src/imgui/*.cpp",

        "examples/imgui_impl_glfw.h",
        "examples/imgui_impl_glfw.cpp",
        "examples/imgui_impl_opengl3.cpp",
        "examples/imgui_impl_opengl3.h"
    }

    includedirs
    {
        "include",
        "../glfw/include",
        "../glad/include"
    }

    filter "system:windows"
        systemversion "latest"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"