#pragma once
#include "ICamera.h"
class OrthographicCamera : public ICamera
{
public:
	const glm::mat4& getViewProjMatrix() const override;
};

