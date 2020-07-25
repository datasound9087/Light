#include "lbpch.h"
#include "App.h"
#include "lightbulb/event/EventDispatcher.h"
#include "lightbulb/graphics/RenderCommands.h"

App* App::instance = nullptr;

App::App()
{
	INFO("Started");
	window = Window::create();
	eventHandler = window->getEventHandler();
	layerStack = std::make_unique<LayerStack>();

	RenderCommands::setViewport(0, 0, 640, 480);
	RenderCommands::setClearColour(glm::vec4(0.0f));

	App::instance = this;
}

void App::run()
{
	init();
	while (running)
	{
		window->onUpdate();
		handleEvents();
		update();
		layerStack->render();
		render();
	}

	shutdown();

	//make window close in debug with console staying open after due to pause
#if CONFIG_DEBUG
	window->shutdown();
#endif
}

void App::handleEvents()
{
	while (eventHandler->hasEvents())
	{
		auto evt = eventHandler->nextEvent();

		event::EventDispatcher dispatcher(evt);
		dispatcher.dispatch<event::WindowClosedEvent>(EVENT_BIND_FUNC(App::WindowClosing));
		dispatcher.dispatch<event::WindowResizedEvent>(EVENT_BIND_FUNC(App::windowResize));

		onEvent(evt);
		layerStack->onEvent(evt);
	}
}

void App::WindowClosing(const std::shared_ptr<event::WindowClosedEvent>& evt)
{
	windowClosing();
	running = false;
}

void App::windowResize(const std::shared_ptr<event::WindowResizedEvent>& evt)
{
	RenderCommands::setViewport(0, 0, evt->getWidth(), evt->getHeight());
}
