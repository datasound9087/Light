#include "LaserApplication.h"

#include "LaserLayer2D.h"
#include "lightbulb/layer/imgui/DebugLayer.h"
#include "lightbulb/graphics/text/Font.h"

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
	RenderCommands::setViewport(0, 0, 640, 480);
	RenderCommands::setClearColour(glm::vec4(0.0f));

	layerStack->pushLayer(std::make_shared<LaserLayer2D>(window->getWidth(), window->getHeight()));
	layerStack->setOverlay(std::make_shared<DebugLayer>());
}
