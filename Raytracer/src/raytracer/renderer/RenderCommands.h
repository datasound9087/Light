#pragma once
#include "RendererAPI.h"

class RenderCommands
{
public:
	static void setClearColour(const glm::vec4& colour);
	static void clear();
	static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	static void drawIndexed(uint32_t count);

private:
	static std::unique_ptr<RendererAPI> renderAPI;
};

