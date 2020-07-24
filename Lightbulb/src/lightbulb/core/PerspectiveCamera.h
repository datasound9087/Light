#pragma once

#include "ICamera.h"

class PerspectiveCamera : public ICamera
{
public:
	PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar);
	PerspectiveCamera(float fov, float aspectRatio);
	PerspectiveCamera(float fov, uint32_t width, uint32_t height);
	virtual ~PerspectiveCamera();
};

