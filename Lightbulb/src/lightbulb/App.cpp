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

	double previous = window->getWindowTime();
	double acumulator = 0.0;
	double timeCounter = 0.0;
	while (running)
	{
		double current = window->getWindowTime();
		double elapsed = current - previous;
		previous = current;
		acumulator += elapsed;
		timeCounter += elapsed;

		window->onUpdate();
		while (acumulator >= 1.0)
		{
			handleEvents();
			layerStack->update();
			update();
			acumulator -= secondsPerUPS;
			ups++;
		}

		if (timeCounter >= 1.0)
		{
			layerStack->tick();
			tick();
			timeCounter = 0.0;
			ups = 0;
			fps = 0;
		}
		
		layerStack->render();
		render();
		fps++;
	}

	shutdown();

	//make window close in debug with console staying open after due to pause
#if CONFIG_DEBUG
	window->shutdown();
#endif
}

void App::setTargetUPS(uint32_t ups)
{
	targetUPS = ups;
	secondsPerUPS = 1.0 / (double)targetUPS;
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
