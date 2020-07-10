#pragma once

struct WindowProps
{
	std::string name;
	uint32_t width;
	uint32_t height;
	bool fullscreen;
	bool vsync;
	bool resizeable;

	WindowProps(const std::string& name = "App",
		uint32_t width = 640,
		uint32_t height = 480,
		bool fullscreen = false,
		bool vsync = true,
		bool resizeable = true)
		: name(name), width(width), height(height), fullscreen(fullscreen), vsync(vsync), resizeable(resizeable)
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

	virtual void* getNativeWindow() const = 0;
};

