#include "CubeRenderer.h"

#include "lightbulb/graphics/RenderCommands.h"

CubeRenderer::CubeRenderer(const std::shared_ptr<ICamera>& camera)
	: camera(camera)
{
	init();
}

void CubeRenderer::init()
{
	float verticies[] =
	{
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
	};

    cubeBuffer = VertexBuffer::create(DataTypes::Types::Float3, 6 * 6, verticies, VertexBuffer::Usage::STATIC);
    cubeShader = Shader::create("cubeRenderer", "C:\\Users\\Sam\\source\\repos\\Light\\CubeLight\\assets\\shaders\\CubeRenderer.glsl");
    cubeBuffer->setBufferLayout(
    {
        {"position", DataTypes::Types::Float3}
    });
    cubeShader->setLayout(cubeBuffer->getLayout());
}


void CubeRenderer::drawCube(const glm::vec3& pos)
{
    cubeBuffer->bind();
    cubeShader->bind();
    cubeShader->setMat4("vp", camera->getViewProjMatrix());
    RenderCommands::drawArrays(DrawType::TRIANGLES, 36);
}
