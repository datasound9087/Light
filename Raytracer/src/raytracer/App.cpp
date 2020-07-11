#include "rtpch.h"
#include "App.h"
#include "raytracer/event/EventDispatcher.h"

App::App()
{
	INFO("Started");
	window = Window::create();
	eventHandler = window->getEventHandler();
}

void App::run()
{
	init();
	while (running)
	{
		handleEvents();
	}

	shutdown();
}

void App::init()
{

}

void App::handleEvents()
{
	window->onUpdate();
	while (eventHandler->hasEvents())
	{
		std::unique_ptr<event::Event> evt = eventHandler->nextEvent();
		event::EventDispatcher dispatcher(evt);
		dispatcher.dispatch<event::WindowClosedEvent>(EVENT_BIND_FUNC(App::onWindowClose));
	}
}

void App::onWindowClose(std::unique_ptr<event::WindowClosedEvent>& evt)
{
	running = false;
}

void App::shutdown()
{
	//if running in debug mode and having console pause to read log
#if CONFIG_DEBUG
	window->shutdown();
#endif
}
