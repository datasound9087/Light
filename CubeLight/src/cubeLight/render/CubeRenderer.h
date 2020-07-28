#pragma once

#include "lightbulb/Lightbulb.h"

class CubeRenderer
{
public:
	CubeRenderer();
	void drawCube();

private:
	void init();

private:
	std::shared_ptr<VertexBuffer> cube;
	std::shared_ptr<Shader> cubeShader;
	std::shared_ptr<TextureAtlas> atlas;
};

