#include "lbpch.h"
#include "Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include "RenderCommands.h"
#include <glm/gtx/string_cast.hpp>

Renderer2D::Renderer2D(const std::shared_ptr<OrthographicCamera> camera)
	: camera(camera)
{
	init();
}

Renderer2D::~Renderer2D()
{
	shutdown();
}

void Renderer2D::setCamera(const std::shared_ptr<OrthographicCamera>& camera)
{
	this->camera = camera;
}

void Renderer2D::beginScene()
{
	shader->setMat4("VP", camera->getViewProjMatrix());
	indexCount = 0;
	quadCount = 0;
	quadVertexBufferPtr = quadVertexBuffer->data();
	nextTextureSlotFree = 0;
	RenderCommands::clear();
}

void Renderer2D::endScene()
{
	size_t sizeUpload = sizeof(VertexData) * 4 * quadCount;
	vertBuffer->setData(quadVertexBuffer->data(), sizeUpload);
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
	glm::mat4 transform = calculateTransform(pos, size, rotation);

	float texIndex = NO_TEXTURE_INDEX;
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

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const std::array<glm::vec4, 4>& cols)
{
	drawQuad(pos, size, 0.0f, cols);
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::array<glm::vec4, 4>& cols)
{
	glm::mat4 transform = calculateTransform(pos, size, rotation);

	float texIndex = NO_TEXTURE_INDEX;
	for (int i = 0; i < QUAD_VERTEX_COUNT; i++)
	{
		drawVertex(i, transform, cols[i], texIndex);
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
	vertBuffer->bind();
	indexBuffer->bind();
	shader->bind();
	for (int i = 0; i < nextTextureSlotFree; i++)
	{
		textureSlots[i]->bind(i);
	}
	RenderCommands::drawIndexed(indexCount);
}

void Renderer2D::init()
{
	vertBuffer = VertexBuffer::create(sizeof(VertexData) * MAX_VERTICIES, VertexBuffer::Usage::DYNAMIC);
	vertBuffer->setBufferLayout(
	{
		{"position", DataTypes::Types::Float2},
		{"texIndex", DataTypes::Types::Int},
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

glm::mat4 Renderer2D::calculateTransform(const glm::vec2& pos, const glm::vec2& size, float rotation)
{
	glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
	if (rotation != 0.0f)
	{
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(-size.x / 2.0f, -size.y / 2.0f, 0.0f)) * transform;
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * transform;
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(size.x / 2.0f, size.y / 2.0f, 0.0f)) * transform;
	}
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f)) * transform;
	return transform;
}

int Renderer2D::addTexture(const std::shared_ptr<Texture2D>& texture)
{
	for (int i = 0; i < nextTextureSlotFree; i++)
	{
		if (textureSlots[i] == texture)
		{
			return i;
		}
	}

	int texIndex = nextTextureSlotFree;
	textureSlots[nextTextureSlotFree] = texture;
	nextTextureSlotFree++;
	return texIndex;
}

void Renderer2D::drawVertex(const uint32_t num, const glm::mat4& transform, const glm::vec4& colour, int texIndex)
{
											//top left	              //top right	           //bot right		        //bot left
	constexpr glm::vec2 textureCoords[] = { {0.0f, 1.0f},           {1.0f, 1.0f},             {1.0f, 0.0f} ,            {0.0f, 0.0f} };
	constexpr glm::vec4 quadCoords[] = { {-0.5f, 1.5f, 0.0f, 1.0f}, {1.5f, 1.5f, 0.0f, 1.0f}, {1.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, 0.0f, 1.0f} };

	//INFO("Vertex {0}: {1}", num, glm::to_string(transform * quadCoords[num]));
	quadVertexBufferPtr->position = transform * quadCoords[num];
	quadVertexBufferPtr->texIndex = texIndex;
	quadVertexBufferPtr->texCoord = textureCoords[num];
	quadVertexBufferPtr->colour = colour;
	quadVertexBufferPtr++;
}

void Renderer2D::reset()
{
}

void Renderer2D::shutdown()
{
}
