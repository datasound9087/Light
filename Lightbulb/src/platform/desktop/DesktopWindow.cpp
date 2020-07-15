#include "lbpch.h"
#include "DesktopWindow.h"

#include "lightbulb/core/Core.h"
#include "lightbulb/event/WindowEvents.h"
#include "lightbulb/event/KeyboardEvents.h"
#include "lightbulb/event/MouseEvents.h"

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
	graphicsContext->swapBuffers();
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
	if (enabled)
	{
		glfwGetWindowPos(window, &windowModeData.x, &windowModeData.y);
		glfwGetWindowSize(window, &windowModeData.width, &windowModeData.height);
		

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, windowModeData.x, windowModeData.y, windowModeData.width, windowModeData.height, 0);
	}
}

void DesktopWindow::showWindow(bool show)
{
	if (show)
		glfwShowWindow(window);
	else
		glfwHideWindow(window);
	props.visible = show;
}

void DesktopWindow::setEventHandler(const std::shared_ptr<event::EventBuffer>& handler)
{
	evtHandler = handler;
	glfwUserPointerData.eventHandler = handler;
}

void DesktopWindow::init()
{
	INFO("Creating window {0} ({1} {2} {3} {4})", props.name, props.width, props.height, props.vsync, props.fullscreen);

	if (getEventHandler() == nullptr)
	{
		setEventHandler(std::make_unique<event::EventBuffer>());
	}

	glfwUserPointerData.eventHandler = getEventHandler();

	if (glfwWindowCount == 0)
	{
		int success = glfwInit();
		ASSERT(success, "Failed to init GLFW");
	}

#ifdef CONFIG_DEBUG
	glfwSetErrorCallback(GLFWErrorCallback);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, props.resizeable);
	
	window = glfwCreateWindow((int)props.width, (int)props.height, props.name.c_str(), nullptr, nullptr);
	glfwWindowCount++;

	glfwSetWindowUserPointer(window, &glfwUserPointerData);

	graphicsContext = GraphicsContext::create(window);
	graphicsContext->init();

	setVsync(props.vsync);

	registerEventCallbacks();

	if (!props.visible)
		showWindow(false);
	else if (props.fullscreen)
		setFullscreen(true);
}

void DesktopWindow::registerEventCallbacks()
{
	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focus)
	{
		GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);
		
		if (focus == GLFW_TRUE)
		{
			std::shared_ptr<event::Event> evt = std::make_shared<event::WindowFocusGainedEvent>();
			data.eventHandler->fireEvent(evt);
		}
		else
		{
			std::shared_ptr<event::Event> evt = std::make_shared<event::WindowFocusLostEvent>();
			data.eventHandler->fireEvent(evt);
		}
	});

	glfwSetWindowPosCallback(window, [](GLFWwindow* window, int xPos, int yPos)
	{
		GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);

		std::shared_ptr<event::Event> evt = std::make_shared<event::WindowMovedEvent>(xPos, yPos);
		data.eventHandler->fireEvent(evt);
	});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{
			GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);

			std::shared_ptr<event::Event> evt = std::make_shared<event::WindowResizedEvent>(width, height);
			data.eventHandler->fireEvent(evt);
	});

	glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
	{
			GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);
			std::shared_ptr<event::Event> evt = std::make_shared<event::WindowClosedEvent>();
			data.eventHandler->fireEvent(evt);
	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
	{
			GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);

			std::shared_ptr<event::Event> evt = std::make_shared<event::MouseScrolledEvent>(xOffset, yOffset);
			data.eventHandler->fireEvent(evt);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
	{
			GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);

			std::shared_ptr<event::Event> evt = std::make_shared<event::MouseMovedEvent>(xPos, yPos);
			data.eventHandler->fireEvent(evt);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
	{
		GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			std::shared_ptr<event::Event> evt = std::make_shared<event::MouseButtonPressedEvent>(button, mods);
			data.eventHandler->fireEvent(evt);
			break;
		}
		case GLFW_RELEASE:
		{
			std::shared_ptr<event::Event> evt = std::make_shared<event::MouseButtonReleasedEvent>(button, mods);
			data.eventHandler->fireEvent(evt);
			break;
		}}
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
	{
		GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			std::shared_ptr<event::Event> evt = std::make_shared<event::KeyboardPressedEvent>(keyCode, mods);
			data.eventHandler->fireEvent(evt);
			break;
		}
		case GLFW_RELEASE:
		{
			std::shared_ptr<event::Event> evt = std::make_shared<event::KeyboardReleasedEvent>(keyCode, mods);
			data.eventHandler->fireEvent(evt);
			break;
		}}
	});

	glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codePoint)
	{
		GLFWUserPointerData& data = *(GLFWUserPointerData*)glfwGetWindowUserPointer(window);

		std::shared_ptr<event::Event> evt = std::make_shared<event::KeyboardTypedEvent>(codePoint);
		data.eventHandler->fireEvent(evt);
	});
}

void DesktopWindow::shutdown()
{
	if (glfwWindowCount > 0)
	{
		glfwDestroyWindow(window);
		glfwWindowCount--;
	}

	if (glfwWindowCount == 0)
	{
		glfwTerminate();
	}
}

double DesktopWindow::getWindowTime()
{
	return glfwGetTime();
}

void DesktopWindow::resizeWindow()
{
	glfwSetWindowSize(window, (int)props.width, (int)props.height);
}
