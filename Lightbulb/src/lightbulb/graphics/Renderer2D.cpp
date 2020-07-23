#include "lbpch.h"
#include "Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include "RenderCommands.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>

														//top left	  //top right	//bot right		//bot left
const std::array<const glm::vec2, 4> Renderer2D::DEFAULT_TEXTURE_COORDS = { glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f) , glm::vec2(0.0f, 0.0f) };
const float Renderer2D::DEFAULT_LINE_THICKNESS = 1.0f;

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
	if (needFlush()) flushReset();

	float texIndex = NO_TEXTURE_INDEX;
	if (texture != nullptr)
	{
		texIndex = addTexture(texture);
	}

	glm::mat4 transform = calculateTransform(pos, size, rotation);
	glm::vec4 topleft = glm::vec4(pos, 0.0f, 1.0f);
	glm::vec4 topRight = glm::vec4(glm::vec2(pos.x + size.x, pos.y), 0.0f, 1.0f);
	glm::vec4 botRight = glm::vec4(pos + size, 0.0f, 1.0f);
	glm::vec4 botLeft = glm::vec4(glm::vec2(pos.x, pos.y + size.y), 0.0f, 1.0f);

	drawVertex(transform * topleft, texIndex, DEFAULT_TEXTURE_COORDS[0], colour);
	drawVertex(transform * topRight, texIndex, DEFAULT_TEXTURE_COORDS[1], colour);
	drawVertex(transform * botRight, texIndex, DEFAULT_TEXTURE_COORDS[2], colour);
	drawVertex(transform * botLeft, texIndex, DEFAULT_TEXTURE_COORDS[3], colour);

	indexCount += 6;
	quadCount++;
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const std::array<glm::vec4, 4>& cols)
{
	drawQuad(pos, size, 0.0f, cols);
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::array<glm::vec4, 4>& cols)
{
	if (needFlush()) flushReset();

	int texIndex = NO_TEXTURE_INDEX;

	glm::mat4 transform = calculateTransform(pos, size, rotation);
	glm::vec4 topleft = glm::vec4(pos, 0.0f, 1.0f);
	glm::vec4 topRight = glm::vec4(glm::vec2(pos.x + size.x, pos.y), 0.0f, 1.0f);
	glm::vec4 botRight = glm::vec4(pos + size, 0.0f, 1.0f);
	glm::vec4 botLeft = glm::vec4(glm::vec2(pos.x, pos.y + size.y), 0.0f, 1.0f);

	drawVertex(transform * topleft, texIndex, DEFAULT_TEXTURE_COORDS[0], cols[0]);
	drawVertex(transform * topRight, texIndex, DEFAULT_TEXTURE_COORDS[1], cols[1]);
	drawVertex(transform * botRight, texIndex, DEFAULT_TEXTURE_COORDS[2], cols[2]);
	drawVertex(transform * botLeft, texIndex, DEFAULT_TEXTURE_COORDS[3], cols[3]);

	indexCount += 6;
	quadCount++;
}

void Renderer2D::drawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& colour, float thickness)
{
	if (needFlush()) flushReset();
	int texIndex = NO_TEXTURE_INDEX;

	glm::vec2 thicknessOffset = glm::vec2(thickness / 2.0f);
	glm::vec4 topleft = glm::vec4(start - thicknessOffset, 0.0f, 1.0f);
	glm::vec4 topRight = glm::vec4(end - thicknessOffset, 0.0f, 1.0f);
	glm::vec4 botRight = glm::vec4(end + thicknessOffset, 0.0f, 1.0f);
	glm::vec4 botLeft = glm::vec4(start + thicknessOffset, 0.0f, 1.0f);
	
	drawVertex(topleft, texIndex, DEFAULT_TEXTURE_COORDS[0], colour);
	drawVertex(topRight, texIndex, DEFAULT_TEXTURE_COORDS[1], colour);
	drawVertex(botRight, texIndex, DEFAULT_TEXTURE_COORDS[2], colour);
	drawVertex(botLeft, texIndex, DEFAULT_TEXTURE_COORDS[3], colour);

	indexCount += 6;
	quadCount++;
}

void Renderer2D::drawLine(const glm::vec2& start, const glm::vec2& end, std::shared_ptr<Texture2D>& texture, float thickness)
{
	if (needFlush()) flushReset();

	int texIndex = NO_TEXTURE_INDEX;
	if (texture != nullptr)
	{
		texIndex = addTexture(texture);
	}

	glm::vec2 thicknessOffset = glm::vec2(thickness / 2.0f);
	glm::vec4 topleft = glm::vec4(start - thicknessOffset, 0.0f, 1.0f);
	glm::vec4 topRight = glm::vec4(end - thicknessOffset, 0.0f, 1.0f);
	glm::vec4 botRight = glm::vec4(end + thicknessOffset, 0.0f, 1.0f);
	glm::vec4 botLeft = glm::vec4(start + thicknessOffset, 0.0f, 1.0f);

	const glm::vec4 WHITE(1.0f);
	drawVertex(topleft, texIndex, DEFAULT_TEXTURE_COORDS[0], WHITE);
	drawVertex(topRight, texIndex, DEFAULT_TEXTURE_COORDS[1], WHITE);
	drawVertex(botRight, texIndex, DEFAULT_TEXTURE_COORDS[2], WHITE);
	drawVertex(botLeft, texIndex, DEFAULT_TEXTURE_COORDS[3], WHITE);

	indexCount += 6;
	quadCount++;
}

void Renderer2D::drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& colour, float thickness)
{
	glm::vec2 topRight = glm::vec2(pos.x + size.x, pos.y);
	glm::vec2 botRight = glm::vec2(pos.x + size.x, pos.y + size.y);
	glm::vec2 botLeft = glm::vec2(pos.x, pos.y + size.y);

	drawLine(pos, topRight, colour, thickness);
	drawLine(topRight, botRight, colour, thickness);
	drawLine(botRight, botLeft, colour, thickness);
	drawLine(botLeft, pos, colour, thickness);
}

void Renderer2D::drawString(const glm::vec2& pos, const std::string& text, const glm::vec4& colour)
{
	if (font == nullptr)
	{
		ERROR("Renderer2D: No set Font");
		return;
	}

	float texIndex = addTexture(font->getAtlas());

	float posOffsetX = pos.x;
	float posOffsetY = pos.y;
	for (const auto& character : text)
	{
		Glyph glyph = font->getGlyph(character);

		glm::vec4 topleft = glm::vec4(posOffsetX, (posOffsetY - glyph.bearing.y), 0.0f, 1.0f);
		glm::vec4 topRight = glm::vec4(posOffsetX + glyph.size.x, (posOffsetY - glyph.bearing.y), 0.0f, 1.0f);
		glm::vec4 botRight = glm::vec4(posOffsetX + glyph.size.x, (posOffsetY - glyph.bearing.y) + glyph.size.y, 0.0f, 1.0f);
		glm::vec4 botLeft = glm::vec4(posOffsetX, (posOffsetY - glyph.bearing.y) + glyph.size.y, 0.0f, 1.0f);

		drawVertex(topleft, texIndex, glyph.texCoord[0], colour);
		drawVertex(topRight, texIndex, glyph.texCoord[1], colour);
		drawVertex(botRight, texIndex, glyph.texCoord[2], colour);
		drawVertex(botLeft, texIndex, glyph.texCoord[3], colour);

		indexCount += 6;
		quadCount++;

		posOffsetX += glyph.advance.x;
		posOffsetY += glyph.advance.y;
	}
}

void Renderer2D::drawString(const glm::vec2& pos, const std::string& text)
{
	drawString(pos, text, glm::vec4(1.0f));
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

	if(RendererAPI::getAPI() == RendererAPI::API::OpenGL)
		shader = Shader::create("Renderer2D", RENDERER_2D_SHADER_SRC_GL, false);

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
	glm::mat4 transform = glm::mat4(1.0f);
	if (rotation != 0.0f)
	{
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(-pos.x - size.x / 2, -pos.y - size.y / 2, 0.0f));
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * transform;
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f)) * transform;
	}
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

void Renderer2D::drawVertex(const glm::vec4& pos, int texIndex, const glm::vec2& texCoord, const glm::vec4& colour)
{
	quadVertexBufferPtr->position = pos;
	quadVertexBufferPtr->texIndex = texIndex;
	quadVertexBufferPtr->texCoord = texCoord;
	quadVertexBufferPtr->colour = colour;
	quadVertexBufferPtr++;
}

bool Renderer2D::needFlush()
{
	return nextTextureSlotFree == textureSlots.size() || quadCount == MAX_QUADS;
}

void Renderer2D::flushReset()
{
	endScene();
	flush();
	beginScene();
}

void Renderer2D::shutdown()
{
}
