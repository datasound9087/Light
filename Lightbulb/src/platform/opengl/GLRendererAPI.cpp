#include "lbpch.h"
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
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
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

void GLRendererAPI::drawIndexed(uint32_t count)
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void GLRendererAPI::drawArrays(const DrawType& type, uint32_t count)
{
	switch (type)
	{
	case DrawType::TRIANGLES:
		glDrawArrays(GL_TRIANGLES, 0, count);
		break;
	case DrawType::LINES:
		glDrawArrays(GL_LINE, 0, count);
		break;
	case DrawType::POINT:
		glDrawArrays(GL_POINT, 0, count);
		break;
	case DrawType::TRIANGLE_STRIP:
		glDrawArrays(GL_TRIANGLE_STRIP, 0, count);
		break;
	default:
		ERROR("Invalid drawType for OpenGL");
	}
}
