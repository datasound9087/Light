#pragma once

#include <lightbulb/Lightbulb.h>

#include "cubeLight/world/World.h"

class CubeLight : public App
{
public:
	void init() override;
	void update() override;
	void render() override;
	void onEvent(const std::shared_ptr<event::Event>& event) override;

private:
	std::unique_ptr<Renderer2D> renderer;
	std::unique_ptr<CameraController> camera;
};

