#pragma once

#include "lightbulb/core/Window.h"
#include "event/WindowEvents.h"
#include "layer/LayerStack.h"

class App
{
public:
	static const App& getApp() { return *instance; }

	App();
	virtual ~App() = default;
	void run();
	const std::shared_ptr<Window>& getWindow() const { return window; }

protected:

	virtual void init() {}
	virtual void update() {}
	virtual void render() {}
	virtual void onEvent(const std::shared_ptr<event::Event>& event) {}
	virtual void windowClosing() {}
	virtual void shutdown() {}

	void shouldClose(bool close) { running = close; }

private:
	void handleEvents();
	void WindowClosing(const std::shared_ptr<event::WindowClosedEvent>& evt);
	void windowResize(const std::shared_ptr<event::WindowResizedEvent>& evt);

protected:
	std::shared_ptr<Window> window;
	std::shared_ptr<event::EventBuffer> eventHandler;

	std::unique_ptr<LayerStack> layerStack;

private:
	bool running = true;
	
	static App* instance;
};

namespace lightbulb
{
	std::unique_ptr<App> createApp();
}

