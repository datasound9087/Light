#pragma once

#include "lightbulb/graphics/GraphicsContext.h"

struct GLFWwindow;

class GLGraphicsContext : public GraphicsContext
{
public:
	GLGraphicsContext(void* window);
	virtual ~GLGraphicsContext() {}

	void init() override;
	void swapBuffers() override;

private:
	GLFWwindow* window;
};

