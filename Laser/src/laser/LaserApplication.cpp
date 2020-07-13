#include "LaserApplication.h"

std::unique_ptr<App> lightbulb::createApp()
{
	return std::make_unique<LaserApplication>();
}

LaserApplication::LaserApplication()
{
}

LaserApplication::~LaserApplication()
{
}

void LaserApplication::init()
{
}

void LaserApplication::update()
{
}

void LaserApplication::render()
{
}

void LaserApplication::onEvent(const std::unique_ptr<event::Event>& event)
{
}

void LaserApplication::shutdown()
{
}
