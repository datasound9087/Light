#include "lbpch.h"
#include "Input.h"

#ifdef API_OPENGL
	#include "DesktopInput.h"
#endif

bool Input::isKeyPressed(int key)
{
#ifdef API_OPENGL
	return DesktopInput::isKeyPressed(key);
#endif
}

bool Input::isMouseButtonPressed(int button)
{
#ifdef API_OPENGL
	return DesktopInput::isMouseButtonPressed(button);
#endif
}

std::pair<float, float> Input::getMousePos()
{
#ifdef API_OPENGL
	return DesktopInput::getMousePos();
#endif
}

float Input::getMouseX()
{
#ifdef API_OPENGL
	return DesktopInput::getMouseX();
#endif
}

float Input::getMouseY()
{
#ifdef API_OPENGL
	return DesktopInput::getMouseY();
#endif
}
