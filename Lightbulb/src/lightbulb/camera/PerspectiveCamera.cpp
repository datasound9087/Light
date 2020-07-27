#include "lbpch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

const float PerspectiveCamera::DEFAULT_Z_NEAR = 0.1f;
const float PerspectiveCamera::DEFAULT_Z_FAR = 100.0f;

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
	: ICamera(glm::perspective(fov, aspectRatio, zNear, zFar), aspectRatio, zNear, zFar),
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

void PerspectiveCamera::onResize(int width, int height)
{
	projMatrix = glm::perspective(fov * zoom, (float)width / (float)height, zNear, zFar);
}
