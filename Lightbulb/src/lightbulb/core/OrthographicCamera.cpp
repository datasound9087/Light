#include "lbpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
{
	setView(left, right, top, bottom);
}

OrthographicCamera::OrthographicCamera(int left, int right, int top, int bottom)
	: OrthographicCamera((float)left, (float)right, (float)top, (float)bottom)
{
}

const glm::mat4& OrthographicCamera::getViewProjMatrix() const
{
	return projection;
}

void OrthographicCamera::setView(int left, int right, int top, int bottom)
{
	setView((float)left, (float)right, (float)top, (float)bottom);
}

void OrthographicCamera::setView(float left, float right, float top, float bottom)
{
	projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}


