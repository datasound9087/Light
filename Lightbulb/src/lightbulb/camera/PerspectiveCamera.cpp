#include "lbpch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
	: ICamera(glm::perspective(fov, aspectRatio, zNear, zFar))
{
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio)
	: PerspectiveCamera(fov, aspectRatio, 0.1f, 100.0f)
{
}

PerspectiveCamera::PerspectiveCamera(float fov, uint32_t width, uint32_t height)
	: PerspectiveCamera(fov, (float)width / (float)height)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}
