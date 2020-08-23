#pragma once

#include <lightbulb/Lightbulb.h>

#include "cubeLight/world/World.h"
#include "cubeLight/render/CubeRenderer.h"

class CubeLight : public App
{
public:
	void init() override;
	void update() override;
	void render() override;
	void onEvent(const std::shared_ptr<event::Event>& event) override;

private:
	std::unique_ptr<CameraController> camera;
	std::unique_ptr<CubeRenderer> cubeRenderer;
};

