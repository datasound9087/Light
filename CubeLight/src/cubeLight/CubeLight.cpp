#include "CubeLight.h"

std::unique_ptr<App> lightbulb::createApp()
{
	return std::make_unique<CubeLight>();
}

void CubeLight::init()
{
	window->captureMouse(true);
	camera = std::make_unique<CameraController>(std::make_shared<PerspectiveCamera>(80.0f, window->getWidth(), window->getHeight()), true, true, true);
	renderer = std::make_unique<Renderer2D>(camera->getCamera());
	camera->getCamera()->setPosition({ 0.0f, 0.0f, 2.0f }); //back 2
	camera->setMovementSpeed(0.1f);
	camera->update();
}

void CubeLight::update()
{
	camera->update();
}

void CubeLight::render()
{
	renderer->beginScene();

	renderer->drawQuad(glm::vec2(-0.5f, -0.5f), glm::vec2(1.0f), glm::vec4(1.0f));

	renderer->endScene();
	renderer->flush();
}

void CubeLight::onEvent(const std::shared_ptr<event::Event>& event)
{
	camera->onEvent(event);
}
