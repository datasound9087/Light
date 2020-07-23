#pragma once
#include "lbpch.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct Glyph
{
	unsigned long codePoint;
	glm::ivec2 size;
	glm::ivec2 bearing;
	glm::ivec2 advance;
	std::array<glm::vec2, 4> texCoord;
};