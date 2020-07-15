#include "lbpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
{
	this->projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

const glm::mat4& OrthographicCamera::getViewProjMatrix() const
{
	return projection;
}
