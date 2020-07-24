#include "lbpch.h"
#include "DesktopInput.h"

#include <GLFW/glfw3.h>
#include "lightbulb/App.h"

bool DesktopInput::isKeyPressed(int key)
{
	auto window = static_cast<GLFWwindow*>(App::getApp().getWindow()->getNativeWindow());
	auto state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool DesktopInput::isMouseButtonPressed(int button)
{
	auto window = static_cast<GLFWwindow*>(App::getApp().getWindow()->getNativeWindow());
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

std::pair<float, float> DesktopInput::getMousePos()
{
	auto window = static_cast<GLFWwindow*>(App::getApp().getWindow()->getNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return { (float)xPos, (float)yPos };
}

float DesktopInput::getMouseX()
{
	auto [x, y] = getMousePos();
	return x;
}

float DesktopInput::getMouseY()
{
	auto [x, y] = getMousePos();
	return y;
}
