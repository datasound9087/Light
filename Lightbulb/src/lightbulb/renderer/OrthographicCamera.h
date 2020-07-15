#pragma once
#include "ICamera.h"
class OrthographicCamera : public ICamera
{
public:
	OrthographicCamera(float left, float right, float top, float bottom);

	const glm::mat4& getViewProjMatrix() const override;
};

