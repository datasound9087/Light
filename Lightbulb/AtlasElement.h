#pragma once

#include "lbpch.h"
#include <glm/vec2.hpp>

struct AtlasElement
{
	glm::ivec2 position;
	glm::ivec2 size;
	std::array<glm::vec2, 4> texCoords;

	AtlasElement(const glm::vec2& position, const glm::vec2& size)
		: position(position), size(size)
	{
		texCoords[0] = position;
		texCoords[1] = glm::vec2(size.x, position.y);
		texCoords[2] = size;
		texCoords[3] = glm::vec2(position.x, size.y);
	}

	void calcTexCoords(float ratioX, float ratioY)
	{
		texCoords[0] = glm::vec2(ratioX * position.x, ratioY * position.y);
		texCoords[1] = glm::vec2(ratioX * (position.x + size.x), ratioY * position.y);
		texCoords[2] = glm::vec2(ratioX * (position.x + size.x), ratioY * (position.y + size.y));
		texCoords[3] = glm::vec2(ratioX * position.x, ratioY * (position.y + size.y));
	}
};
