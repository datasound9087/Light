#pragma once

#include "lightbulb/camera/ICamera.h"
#include "lightbulb/graphics/resource/shader/Shader.h"
#include "lightbulb/graphics/resource/buffer/VertexBuffer.h"

class CubeRenderer
{
public:
	CubeRenderer(const std::shared_ptr<ICamera>& camera);
	void drawCube(const glm::vec3& pos);

private:
	void init();

private:
	std::shared_ptr<VertexBuffer> cubeBuffer;
	std::shared_ptr<Shader> cubeShader;

	std::shared_ptr<ICamera> camera;
};

