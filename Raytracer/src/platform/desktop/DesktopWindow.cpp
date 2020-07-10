#include "rtpch.h"
#include "DesktopWindow.h"

#include "raytracer/core/Core.h"

static uint8_t glfwWindowCount = 0;

static void GLFWErrorCallback(int error, const char* desc)
{
	ERROR("GLFW Error ({0}): {1}", error, desc);
}

DesktopWindow::DesktopWindow(const WindowProps& props)
	:props(props)
{
	init();
}

DesktopWindow::~DesktopWindow()
{
	shutdown();
}

void DesktopWindow::onUpdate()
{
	glfwPollEvents();
}

void DesktopWindow::setWidth(const uint32_t winWidth)
{
	props.width = winWidth;
	resizeWindow();
}

void DesktopWindow::setHeight(const uint32_t winHeight)
{
	props.height = winHeight;
	resizeWindow();
}

void DesktopWindow::setVsync(const bool enabled)
{
	props.vsync = enabled;
	glfwSwapInterval(props.vsync);
}

void DesktopWindow::setFullscreen(const bool enabled)
{
}

void DesktopWindow::init()
{
	INFO("Creating window {0} ({1} {2} {3} {4})", props.name, props.width, props.height, props.vsync, props.fullscreen);

	if (glfwWindowCount == 0)
	{
		int success = glfwInit();
		ASSERT(success, "Failed to init GLFW");

#if CONFIG_DEBUG
		glfwSetErrorCallback(GLFWErrorCallback);
#endif
	}

#ifdef CONFIG_DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, props.resizeable);
	
	window = glfwCreateWindow((int)props.width, (int)props.height, props.name.c_str(), nullptr, nullptr);
	glfwWindowCount++;

	graphicsContext = GraphicsContext::create(window);
	graphicsContext->init();

	setVsync(props.vsync);
}

void DesktopWindow::shutdown()
{
	glfwDestroyWindow(window);
	glfwWindowCount--;

	if (glfwWindowCount == 0)
	{
		glfwTerminate();
	}
}

void DesktopWindow::resizeWindow()
{
}
