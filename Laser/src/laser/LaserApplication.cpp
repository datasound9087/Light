#include "LaserApplication.h"

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lightbulb/renderer/Colour.h"

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

	testTexture = Texture2D::create("test", "C:\\Users\\Sam\\source\\repos\\Light\\Laser\\assets\\textures\\test.png");
	std::shared_ptr<OrthographicCamera> camera = std::make_shared<OrthographicCamera>(0.0f, 640.0f, 0.0f, 480.0f);
	renderer = std::make_unique<Renderer2D>(camera);
}

void LaserApplication::update()
{
}

void LaserApplication::render()
{
	renderer->beginScene();
	renderer->drawQuad(glm::vec2(300.0, 300.0f), glm::vec2(100.0f, 100.0f), 100.0f * window->getWindowTime(), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	std::array<glm::vec4, 4> cols = {colour::COL_BLACK, colour::COL_BLUE, colour::COL_GREEN, colour::COL_RED};
	renderer->drawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), 0.0f, testTexture, glm::vec4(0.9f, 0.0f, 0.0f, 1.0f));
	renderer->drawQuad(glm::vec2(100.0f, 100.0f), glm::vec2(50.0f, 50.0f), cols);
	renderer->endScene();
	renderer->flush();
}

void LaserApplication::onEvent(const std::unique_ptr<event::Event>& event)
{
}

void LaserApplication::shutdown()
{
}
