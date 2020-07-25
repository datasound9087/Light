#include "CubeLight.h"

std::unique_ptr<App> lightbulb::createApp()
{
	return std::make_unique<CubeLight>();
}

void CubeLight::init()
{
	world = std::make_unique<World>("Test");
}

void CubeLight::update()
{
}

void CubeLight::render()
{
}
