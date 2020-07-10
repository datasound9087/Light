#include "rtpch.h"
#include "GLRendererAPI.h"

#include <glad/glad.h>

void glMessageCallback(
	unsigned source,
	unsigned type,
	unsigned id,
	unsigned severity,
	int length,
	const char* message,
	const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		CRITICAL(message);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		ERROR(message);
		break;
	case GL_DEBUG_SEVERITY_LOW:
		WARN(message);
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		TRACE(message);
		break;
	}
}

GLRendererAPI::~GLRendererAPI()
{
}

void GLRendererAPI::init()
{
#if CONFIG_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
}

void GLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void GLRendererAPI::setClearColour(const glm::vec4& colour)
{
	glClearColor(colour.r, colour.g, colour.b, colour.a);
}

void GLRendererAPI::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
