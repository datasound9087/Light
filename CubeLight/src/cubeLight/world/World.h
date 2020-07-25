#pragma once

#include "lbpch.h"
#include "cubeLight/block/Block.h"

class World
{
public:
	World(const std::string& name);
private:
	std::string name;

	std::vector<Block> blocks;
};

