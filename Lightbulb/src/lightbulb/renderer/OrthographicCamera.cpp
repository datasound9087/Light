#include "lbpch.h"
#include "OrthographicCamera.h"

const glm::mat4& OrthographicCamera::getViewProjMatrix() const
{
	return glm::mat4(1.0f);
}
