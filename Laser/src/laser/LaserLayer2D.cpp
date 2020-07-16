#include "LaserLayer2D.h"
#include "lightbulb/core/OrthographicCamera.h"
#include "lightbulb/graphics/Colour.h"

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
	//FIX THIS - COORDINATES NOT CORRECT FOR EACH VERTEX
	renderer->drawQuad(glm::vec2(0.0f), glm::vec2(100.0f), colour::COL_RED);
	renderer->drawQuad(glm::vec2(100.0f), glm::vec2(100.0f), colour::COL_GREEN);
	renderer->drawQuad(glm::vec2(200.0f), glm::vec2(100.0f), colour::COL_BLUE);

	renderer->drawQuad(glm::vec2(200.0f), glm::vec2(100.0f), 45.0f, colour::COL_WHITE);

	//line testing
	//horizontal
	renderer->drawLine(glm::vec2(200.0f, 10.0f), glm::vec2(250.0f, 10.0f), colour::COL_RED);
	renderer->drawLine(glm::vec2(250.0f, 20.0f), glm::vec2(200.0f, 20.0f), colour::COL_RED);
	//vertical
	renderer->drawLine(glm::vec2(300.0f, 10.0f), glm::vec2(300.0f, 60.0f), colour::COL_RED);
	renderer->drawLine(glm::vec2(310.0f, 60.0f), glm::vec2(310.0f, 10.0f), colour::COL_RED);
	//diags
	renderer->drawLine(glm::vec2(400.0f, 10.0f), glm::vec2(350.0f, 80.0f), colour::COL_GREEN);
	renderer->drawLine(glm::vec2(380.0f, 80.0f), glm::vec2(430.0f, 10.0f), colour::COL_GREEN);

	renderer->drawRect(glm::vec2(500.0f, 20.0f), glm::vec2(30.0f), colour::COL_WHITE);
}
