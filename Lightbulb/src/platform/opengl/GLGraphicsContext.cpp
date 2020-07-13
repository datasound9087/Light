#include "lbpch.h"
#include "GLGraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLGraphicsContext::GLGraphicsContext(void* winHandle)
{
	ASSERT(window, "Window null");
	window = static_cast<GLFWwindow*>(winHandle);
}

void GLGraphicsContext::init()
{
	glfwMakeContextCurrent(window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ASSERT(status, "GLAD init failed");
	
	INFO("OpenGL Info:");
	INFO("    Vendor: {0}", glGetString(GL_VENDOR));
	INFO("    renderer: {0}", glGetString(GL_RENDERER));
	INFO("    Version: {0}", glGetString(GL_VERSION));

#ifdef ENABLE_ASSERTS
	int vMajor, vMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &vMajor);
	glGetIntegerv(GL_MINOR_VERSION, &vMinor);
	ASSERT(vMajor == 4 && vMinor >= 5, "OpenGL 4.5 required");
#endif
}

void GLGraphicsContext::swapBuffers()
{
	glfwSwapBuffers(window);
}
