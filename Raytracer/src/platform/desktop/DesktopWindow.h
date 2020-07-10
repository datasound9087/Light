#pragma once

#include "raytracer/core/Window.h"
#include <GLFW/glfw3.h>

#include "raytracer/renderer/GraphicsContext.h"

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

	void* getNativeWindow() const override { return window; }

private:
	void init();
	void shutdown();
	void resizeWindow();

private:

	GLFWwindow* window;
	WindowProps props;

	std::unique_ptr<GraphicsContext> graphicsContext;
};

