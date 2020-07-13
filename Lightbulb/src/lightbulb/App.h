#pragma once

#include "lightbulb/core/Window.h"
#include "event/WindowEvents.h"

class App
{
public:

	App();
	virtual ~App() = default;
	void run();

protected:

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void onEvent(const std::unique_ptr<event::Event>& event) = 0;
	virtual void windowClosing() {}
	virtual void shutdown() = 0;

	void shouldClose(bool close) { running = close; }

private:
	void handleEvents();
	void WindowClosing(std::unique_ptr<event::WindowClosedEvent>& evt);

protected:
	std::shared_ptr<event::EventBuffer> eventHandler;

private:
	std::unique_ptr<Window> window;
	bool running = true;
};

namespace lightbulb
{
	std::unique_ptr<App> createApp();
}

