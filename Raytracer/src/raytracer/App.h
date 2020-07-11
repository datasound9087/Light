#pragma once

#include "raytracer/core/Window.h"
#include "raytracer/event/WindowEvents.h"

class App
{
public:
	App();
	void run();

private:

	void init();
	void handleEvents();
	void onWindowClose(std::unique_ptr<event::WindowClosedEvent>& evt);
	void shutdown();

private:
	std::unique_ptr<Window> window;
	std::shared_ptr<event::EventBuffer> eventHandler;
	bool running = true;
};

