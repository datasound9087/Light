#pragma once

#include "raytracer/core/Window.h"

class App
{
public:
	App();
	void run();

private:
	std::unique_ptr<Window> window;
	bool running = true;
};

