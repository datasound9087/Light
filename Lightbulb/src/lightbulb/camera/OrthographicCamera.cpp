#include "lbpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

const float OrthographicCamera::DEFAULT_Z_NEAR = -1.0f;
const float OrthographicCamera::DEFAULT_Z_FAR = 1.0f;

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
	: ICamera(glm::ortho(left, right, bottom, top, DEFAULT_Z_NEAR, DEFAULT_Z_FAR), calcAspectRatio(left, right, top, bottom), DEFAULT_Z_NEAR, DEFAULT_Z_FAR),
	left(left), right(right), top(top), bottom(bottom)
{
}

OrthographicCamera::OrthographicCamera(int left, int right, int top, int bottom)
	: OrthographicCamera((float)left, (float)right, (float)top, (float)bottom)
{
}

void OrthographicCamera::setView(int left, int right, int top, int bottom)
{
	setView((float)left, (float)right, (float)top, (float)bottom);
}

void OrthographicCamera::setView(float left, float right, float top, float bottom)
{
	projMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void OrthographicCamera::onResize(int width, int height)
{
	right = width;
	if (top > bottom)
		top = height;
	else
		bottom = height;

	setView(left, right, top, bottom);
}

float OrthographicCamera::calcAspectRatio(float left, float right, float top, float bottom)
{
	return glm::abs(right - left) / glm::abs(bottom - top);
}


