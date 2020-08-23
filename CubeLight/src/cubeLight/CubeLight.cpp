#include "CubeLight.h"

std::unique_ptr<App> lightbulb::createApp()
{
	return std::make_unique<CubeLight>();
}

void CubeLight::init()
{
	window->captureMouse(true);
	camera = std::make_unique<CameraController>(std::make_shared<PerspectiveCamera>(80.0f, window->getWidth(), window->getHeight()), true, true, true);
	camera->getCamera()->setPosition({ 0.0f, 0.0f, 2.0f }); //back 2
	camera->setMovementSpeed(0.1f);
	camera->update();

	cubeRenderer = std::make_unique<CubeRenderer>(camera->getCamera());
}

void CubeLight::update()
{
	camera->update();
}

void CubeLight::render()
{
	RenderCommands::clear();
	cubeRenderer->drawCube({ 0.0f, 0.0f, 0.0f });
}

void CubeLight::onEvent(const std::shared_ptr<event::Event>& event)
{
	camera->onEvent(event);
}
