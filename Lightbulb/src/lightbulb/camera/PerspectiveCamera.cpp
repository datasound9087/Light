#include "lbpch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

const float PerspectiveCamera::DEFAULT_Z_NEAR = 0.1f;
const float PerspectiveCamera::DEFAULT_Z_FAR = 100.0f;

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
	: ICamera(glm::perspective(fov, aspectRatio, zNear, zFar), aspectRatio, zNear, zFar, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, {0.0f, 1.0f, 0.0f}),
	fov(fov)
{
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio)
	: PerspectiveCamera(fov, aspectRatio, DEFAULT_Z_NEAR, DEFAULT_Z_FAR)
{
}

PerspectiveCamera::PerspectiveCamera(float fov, uint32_t width, uint32_t height)
	: PerspectiveCamera(fov, (float)width / (float)height)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::move(const Direction& dir, float amount)
{
	switch (dir)
	{
	case Direction::LEFT:
		position += right * amount;
		break;
	case Direction::RIGHT:
		position -= right * amount;
		break;
	case Direction::UP:
		position += direction * amount;
		break;
	case Direction::DOWN:
		position -= direction * amount;
		break;
	}
}

void PerspectiveCamera::onResize(int width, int height)
{
	projMatrix = glm::perspective(fov * zoom, (float)width / (float)height, zNear, zFar);
}
