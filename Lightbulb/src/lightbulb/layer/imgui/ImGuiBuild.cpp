#include "lbpch.h"
#include "ImGuiBuild.h"
#include "lightbulb/App.h"

#ifdef PLATFORM_WINDOWS
	#include "imgui_impl_glfw.h"
#else
	#error "Not yet supported"
#endif

#ifdef API_OPENGL
	#define IMGUI_IMPL_OPENGL_LOADER_GLAD
	#include "imgui_impl_opengl3.h"
#else
	#error "Not yet supported"
#endif


void imguiBuild::init()
{
#if defined(PLATFORM_WINDOWS) && defined(API_OPENGL)
	ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(App::getApp().getWindow()->getNativeWindow()), true);
	ImGui_ImplOpenGL3_Init("#version 410");
#else
	#error "Not yet supported"
#endif
}

void imguiBuild::begin()
{
#if defined(PLATFORM_WINDOWS) && defined(API_OPENGL)
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
#else
	#error "Not yet supported"
#endif
}

void imguiBuild::end()
{
}

void imguiBuild::render()
{
#if defined(API_OPENGL)
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#else
	#error "Not yet supported"
#endif
}

void imguiBuild::shutdown()
{
#if defined(PLATFORM_WINDOWS) && defined(API_OPENGL)
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
#else
	#error "Not yet supported"
#endif
}
