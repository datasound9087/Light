#pragma once

#include "lightbulb/core/Window.h"
#include <GLFW/glfw3.h>

#include "lightbulb/renderer/GraphicsContext.h"

class DesktopWindow : public Window
{
public:
	DesktopWindow(const WindowProps& props);
	virtual ~DesktopWindow();

	void onUpdate() override;
	uint32_t getWidth() const override { return props.width; }
	void setWidth(const uint32_t width) override;
	uint32_t getHeight() const override { return props.height; }
	void setHeight(const uint32_t height) override;

	bool isVsync() const override { return props.vsync; }
	void setVsync(const bool enabled) override;
	bool isFullscreen() const override { return props.fullscreen; };
	void setFullscreen(const bool enabled) override;
	bool isResizeable() const override { return props.resizeable; };
	void showWindow(bool show) override;
	void shutdown() override;

	double getWindowTime() override;

	void setEventHandler(const std::shared_ptr<event::EventBuffer>& handler) override;

	void* getNativeWindow() const override { return window; }

private:
	void init();
	void registerEventCallbacks();
	void resizeWindow();

private:

	GLFWwindow* window;
	WindowProps props;

	std::unique_ptr<GraphicsContext> graphicsContext;

	struct WindowedModeData
	{
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
	} windowModeData;

	struct GLFWUserPointerData
	{
		std::shared_ptr<event::EventBuffer> eventHandler;
	} glfwUserPointerData;
};

