#pragma once

#include "ICamera.h"

class PerspectiveCamera : public ICamera
{
public:
	static const float DEFAULT_Z_NEAR;
	static const float DEFAULT_Z_FAR;
public:
	PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar);
	PerspectiveCamera(float fov, float aspectRatio);
	PerspectiveCamera(float fov, uint32_t width, uint32_t height);
	virtual ~PerspectiveCamera();

	void onResize(int width, int height) override;

private:
	float fov;
};

