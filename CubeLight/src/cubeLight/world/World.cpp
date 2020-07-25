#include "World.h"

World::World(const std::string& name)
	: name(name)
{
	blocks.push_back(Block(0, 0, 0));
}
