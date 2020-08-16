#pragma once
#include "ICamera.h"
class OrthographicCamera : public ICamera
{
public:
	static const float DEFAULT_Z_NEAR;
	static const float DEFAULT_Z_FAR;
public:

	OrthographicCamera(float left, float right, float top, float bottom);
	OrthographicCamera(int left, int right, int top, int bottom);

	void move(const Direction& dir, float amount) override;

	void setView(int left, int right, int top, int bottom);
	void setView(float left, float right, float top, float bottom);

	void onResize(int width, int height) override;

private:
	float calcAspectRatio(float left, float right, float top, float bottom);

private:
	float winLeft;
	float winRight;
	float winTop;
	float winBottom;
};