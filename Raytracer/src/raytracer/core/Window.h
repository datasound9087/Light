#pragma once

#include "raytracer/event/EventBuffer.h";

struct WindowProps
{
	std::string name;
	uint32_t width;
	uint32_t height;
	bool fullscreen;
	bool vsync;
	bool resizeable;
	bool visible;

	WindowProps(const std::string& name = "App",
		uint32_t width = 640,
		uint32_t height = 480,
		bool fullscreen = false,
		bool vsync = true,
		bool resizeable = true,
		bool visible = true)
		: name(name), width(width), height(height), fullscreen(fullscreen), vsync(vsync), resizeable(resizeable), visible(visible)
	{}
};

class Window
{
public:
	static std::unique_ptr<Window> create(const WindowProps& props = WindowProps());

	virtual ~Window() = default;
	virtual void onUpdate() = 0;

	virtual uint32_t getWidth() const = 0;
	virtual void setWidth(const uint32_t width) = 0;
	virtual uint32_t getHeight() const = 0;
	virtual void setHeight(const uint32_t height) = 0;
	virtual bool isVsync() const = 0;
	virtual void setVsync(const bool enabled) = 0;
	virtual bool isFullscreen() const = 0;
	virtual void setFullscreen(const bool enabled) = 0;
	virtual bool isResizeable() const = 0;
	virtual void showWindow(bool show) = 0;
	virtual void shutdown() = 0;

	virtual void setEventHandler(const std::shared_ptr<event::EventBuffer>& handler) = 0;
	std::shared_ptr<event::EventBuffer> getEventHandler() const { return evtHandler; }

	virtual void* getNativeWindow() const = 0;

protected:
	std::shared_ptr<event::EventBuffer> evtHandler;
};

