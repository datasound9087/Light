#include "lbpch.h"
#include "RenderCommands.h"

std::unique_ptr<RendererAPI> RenderCommands::renderAPI = RendererAPI::create();

void RenderCommands::setClearColour(const glm::vec4& colour)
{
	renderAPI->setClearColour(colour);
}

void RenderCommands::clear()
{
	renderAPI->clear();
}

void RenderCommands::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	renderAPI->setViewport(x, y, width, height);
}

void RenderCommands::drawIndexed(uint32_t count)
{
	renderAPI->drawIndexed(count);
}
