#pragma once

#include <glm/vec3.hpp>

#include "cubeLight/render/BlockTexture.h"

class Block
{
public:
	Block(int x, int y, int z);

	const glm::vec3& getPosition() { return position; }
private:
	std::string name;
	glm::ivec3 position;
	BlockTexture texture;
};