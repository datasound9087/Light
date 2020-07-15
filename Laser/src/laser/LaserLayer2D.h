#pragma once
#include "lightbulb/layer/Layer2D.h"

class LaserLayer2D : public Layer2D
{
public:
	LaserLayer2D(uint32_t width, uint32_t height);
	virtual ~LaserLayer2D();

	void init() override;
	void onEvent(const std::shared_ptr<event::Event>& evt) override;
	void update() override;
	void render() override;
};

