#include "rtpch.h"
#include "App.h"

App::App()
{
	INFO("Started");
	window = Window::create();
}

void App::run()
{
	while (running)
	{
		window->onUpdate();
	}
}
