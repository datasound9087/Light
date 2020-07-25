#pragma once
#include "lbpch.h"

class Input
{
public:
	static bool isKeyPressed(int key);
	static bool isMouseButtonPressed(int button);
	static std::pair<float, float> getMousePos();
	static float getMouseX();
	static float getMouseY();
};

