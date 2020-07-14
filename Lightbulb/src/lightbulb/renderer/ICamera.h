#pragma once
#include <glm/mat4x4.hpp>

class ICamera
{
public:
	virtual const glm::mat4& getViewProjMatrix() const = 0;

protected:
	glm::mat4 projection;
};
