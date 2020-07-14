#include "lbpch.h"
#include "Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>

Renderer2D::Renderer2D(const OrthographicCamera& camera)
	: camera(camera)
{
	init();
}

Renderer2D::~Renderer2D()
{
	shutdown();
}

void Renderer2D::setCamera(const OrthographicCamera& camera)
{
	this->camera = camera;
}

void Renderer2D::beginScene()
{
	shader->setMat4("VP", camera.getViewProjMatrix());
	indexCount = 0;
	quadCount = 0;
	quadVertexBufferPtr = quadVertexBuffer->data();
	nextTextureSlotFree = 0;
}

void Renderer2D::endScene()
{
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& colour)
{
	drawQuad(pos, size, 0.0f, nullptr, colour);
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture)
{
	drawQuad(pos, size, 0.0f, texture, glm::vec4(1.0f));
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture)
{
	drawQuad(pos, size, rotation, texture, glm::vec4(1.0f));
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& colour)
{
	drawQuad(pos, size, rotation, nullptr, colour);
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const glm::vec4& colour)
{
	constexpr uint32_t QUAD_VERTEX_COUNT = 4;
	
	glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
	if (rotation != 0.0f)
		transform = transform * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = transform * glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 1.0f));

	float texIndex = -1.0f;
	if (texture != nullptr)
	{
		texIndex = addTexture(texture);
	}
		
	for (int i = 0; i < QUAD_VERTEX_COUNT; i++)
	{
		drawVertex(i, transform, colour, texIndex);
	}
	indexCount += 6;
	quadCount++;
}

void Renderer2D::drawLine(const glm::vec2& start, const glm::vec2& end, float thickness, const glm::vec4& colour)
{
	//maths
}

void Renderer2D::flush()
{
	for (int i = 0; i < nextTextureSlotFree; i++)
	{
		textureSlots[i]->bind(i);
	}
}

void Renderer2D::init()
{
	vertBuffer = VertexBuffer::create(DataTypes::Types::Float, MAX_QUADS, VertexBuffer::Usage::DYNAMIC);
	vertBuffer->setBufferLayout(
	{
		{"position", DataTypes::Types::Float2},
		{"texIndex", DataTypes::Types::Float},
		{"texCoord", DataTypes::Types::Float2},
		{"colour", DataTypes::Types::Float4}
	});

	quadVertexBuffer = std::make_unique<std::array<VertexData, MAX_VERTICIES>>();

	shader = Shader::create("Renderer2D", RENDERER_2D_SHADER_SRC, false);
	shader->setLayout(vertBuffer->getLayout());

	int32_t samplers[MAX_TEXTURES];
	for (int i = 0; i < MAX_TEXTURES; i++)
		samplers[i] = i;
	shader->setIntArray("textureSamplers", samplers, MAX_TEXTURES);

	uint32_t* indicies = new uint32_t[MAX_INDICIES];
	uint32_t offset = 0;
	for (uint32_t i = 0; i < MAX_INDICIES; i += 6)
	{
		indicies[i + 0] = offset + 0;
		indicies[i + 1] = offset + 1;
		indicies[i + 2] = offset + 2;

		indicies[i + 3] = offset + 0;
		indicies[i + 4] = offset + 2;
		indicies[i + 5] = offset + 3;

		offset += 4;
	}

	indexBuffer = IndexBuffer::create(MAX_INDICIES, indicies);
	delete[] indicies;
}

float Renderer2D::addTexture(const std::shared_ptr<Texture2D>& texture)
{

}

void Renderer2D::drawVertex(const uint32_t num, const glm::mat4& transform, const glm::vec2& colour, float texIndex)
{
											//top left	  //top right	//bot right		//bot left
	constexpr glm::vec2 textureCoords[] = { {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} , {0.0f, 0.0f} };
	constexpr glm::vec4 quadCoords[] = { {-0.5f, 1.5f, 0.0f, 1.0f}, {1.5f, 1.5f, 0.0f, 1.0f}, {1.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, 0.0f, 1.0f} };

	quadVertexBufferPtr->position = transform * quadCoords[num];
	quadVertexBufferPtr->texIndex = texIndex;
	quadVertexBufferPtr->texCoord = textureCoords[num];
	quadVertexBufferPtr++;
}

void Renderer2D::reset()
{
}

void Renderer2D::shutdown()
{
}