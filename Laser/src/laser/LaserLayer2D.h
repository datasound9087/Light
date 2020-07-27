#pragma once
#include "lightbulb/layer/Layer2D.h"
#include "lightbulb/event/WindowEvents.h"
#include "lightbulb/camera/CameraController.h"

class LaserLayer2D : public Layer2D
{
public:
	LaserLayer2D(int width, int height);
	virtual ~LaserLayer2D();

	void init() override;
	void layerUpdate() override;
	void render() override;

private:
	std::unique_ptr<CameraController> controller;
};

