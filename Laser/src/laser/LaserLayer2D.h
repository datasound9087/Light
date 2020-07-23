#pragma once
#include "lightbulb/layer/Layer2D.h"
#include "lightbulb/event/WindowEvents.h"

class LaserLayer2D : public Layer2D
{
public:
	LaserLayer2D(int width, int height);
	virtual ~LaserLayer2D();

	void init() override;
	void update() override;
	void render() override;
};

