#include "lbpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
{
	this->projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

const glm::mat4& OrthographicCamera::getViewProjMatrix() const
{
	return projection;
}
