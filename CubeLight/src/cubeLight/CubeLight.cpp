#include "CubeLight.h"

std::unique_ptr<App> lightbulb::createApp()
{
	return std::make_unique<CubeLight>();
}

void CubeLight::init()
{
}

void CubeLight::update()
{
}

void CubeLight::render()
{
}

void CubeLight::onEvent(const std::shared_ptr<event::Event>& event)
{
}
