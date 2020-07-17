#pragma once
#include <glm/vec2.hpp>

struct Glyph
{
	unsigned long codePoint;
	glm::ivec2 size;
	glm::ivec2 bearing;
	uint32_t advance;
	glm::vec2 texCoord;
};