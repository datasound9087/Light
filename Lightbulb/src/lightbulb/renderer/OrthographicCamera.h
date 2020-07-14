#pragma once
#include "ICamera.h"
class OrthographicCamera : public ICamera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top, float zNear = 0.0f, float zFar = 1.0f);

	const glm::mat4& getViewProjMatrix() const override;
};

