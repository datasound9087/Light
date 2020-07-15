#include "LaserLayer2D.h"
#include "lightbulb/core/OrthographicCamera.h"
#include "lightbulb/renderer/Colour.h"

LaserLayer2D::LaserLayer2D(uint32_t width, uint32_t height)
	: Layer2D("LaserLayer2D", std::make_shared<OrthographicCamera>(0, width, 0, height))
{
}

LaserLayer2D::~LaserLayer2D()
{
}

void LaserLayer2D::init()
{
}

void LaserLayer2D::onEvent(const std::shared_ptr<event::Event>& evt)
{
}

void LaserLayer2D::update()
{
}

void LaserLayer2D::render()
{
	//renderer->drawRect(glm::vec2(0.0f), glm::vec2(100.0f), colour::COL_WHITE);

	//renderer->drawLine(glm::vec2(200.0f), glm::vec2(250.0f, 200.0f), colour::COL_WHITE);
	//renderer->drawLine(glm::vec2(250.0f, 200.0f), glm::vec2(250.0f, 250.0f), colour::COL_WHITE);

	//renderer->drawQuad(glm::vec2(200.0f), glm::vec2(10.0f), colour::COL_RED);

	renderer->drawQuad(glm::vec2(630.0f, 0.0f), glm::vec2(5.0f), colour::COL_RED);
	renderer->drawLine(glm::vec2(630.0f, 10.0f), glm::vec2(400.0f, 10.0f), colour::COL_WHITE);
}
