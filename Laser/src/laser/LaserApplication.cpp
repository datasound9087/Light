#include "LaserApplication.h"

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

std::unique_ptr<App> lightbulb::createApp()
{
	return std::make_unique<LaserApplication>();
}

const std::string SHADER_SRC =
"#type vertex\n"
"#version 450 core\n"
"layout(location = 0) in vec2 position;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 0.0, 1.0);\n"
"}\n"
"#type fragment\n"
"#version 450 core\n"
"out vec4 fragColour;\n"
"void main()\n"
"{\n"
"    fragColour = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";

struct VertexData
{
	glm::vec2 position;
	float texIndex = -1.0f;
	glm::vec2 texCoord = glm::vec2(1.0f);
	glm::vec4 colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	VertexData(glm::vec2 pos)
		: position(pos)
	{}
};

LaserApplication::LaserApplication()
{
}

LaserApplication::~LaserApplication()
{
}

void LaserApplication::init()
{
}

void LaserApplication::update()
{
}

void LaserApplication::render()
{
}

void LaserApplication::onEvent(const std::unique_ptr<event::Event>& event)
{
}

void LaserApplication::shutdown()
{
}
