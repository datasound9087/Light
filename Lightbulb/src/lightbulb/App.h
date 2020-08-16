#pragma once

#include "lightbulb/core/Window.h"
#include "event/WindowEvents.h"
#include "event/KeyboardEvents.h"
#include "layer/LayerStack.h"

class App
{
public:
	static const uint32_t DEFAULT_UPS = 60;

public:
	static const App& getApp() { return *instance; }

	App();
	virtual ~App() = default;
	void run();
	const std::shared_ptr<Window>& getWindow() const { return window; }

	uint32_t getTargetUPS() const { return targetUPS; }
	void setTargetUPS(uint32_t ups);

	double getCurrentUPS() const { return ups; }
	double getCurrentFPS() const { return fps; }

protected:

	virtual void init() {}
	virtual void update() {}
	virtual void tick() {}
	virtual void render() {}
	virtual void onEvent(const std::shared_ptr<event::Event>& event) {}
	virtual void windowClosing() {}
	virtual void shutdown() {}

	void shouldClose(bool close) { running = close; }

private:
	void handleEvents();
	void WindowClosing(const std::shared_ptr<event::WindowClosedEvent>& evt);
	void windowResize(const std::shared_ptr<event::WindowResizedEvent>& evt);
	void handleInternalKeys(const std::shared_ptr<event::KeyboardPressedEvent>& evt);

protected:
	std::shared_ptr<Window> window;
	std::shared_ptr<event::EventBuffer> eventHandler;

	std::unique_ptr<LayerStack> layerStack;

private:
	bool running = true;
	uint32_t targetUPS = DEFAULT_UPS;
	double secondsPerUPS = 1.0 / (double)targetUPS;

	double ups = 0;
	double fps = 0;

	static App* instance;
};

namespace lightbulb
{
	std::unique_ptr<App> createApp();
}

