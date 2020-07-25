#pragma once

#include <lightbulb/Lightbulb.h>

#include "cubeLight/world/World.h"

class CubeLight : public App
{
public:
	void init() override;
	virtual void update() override;
	virtual void render() override;

private:
	std::unique_ptr<World> world;
};

