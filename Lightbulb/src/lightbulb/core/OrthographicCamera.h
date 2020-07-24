#pragma once
#include "ICamera.h"
class OrthographicCamera : public ICamera
{
public:
	OrthographicCamera(float left, float right, float top, float bottom);
	OrthographicCamera(int left, int right, int top, int bottom);

	void setView(int left, int right, int top, int bottom);
	void setView(float left, float right, float top, float bottom);
};

