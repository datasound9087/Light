#pragma once

#include <glm/vec3.hpp>

class Block
{
public:
	Block(int x, int y, int z);

	const glm::vec3& getPosition() { return position; }
private:
	glm::ivec3 position;
};