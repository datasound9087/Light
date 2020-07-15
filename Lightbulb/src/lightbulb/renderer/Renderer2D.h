#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "resource/texture/Texture2D.h"
#include "resource/buffer/VertexBuffer.h"
#include "resource/buffer/IndexBuffer.h"
#include "resource/shader/Shader.h"
#include "OrthographicCamera.h"

class Renderer2D
{
public:
	Renderer2D(const std::shared_ptr<OrthographicCamera> camera);
	~Renderer2D();
	void setCamera(const std::shared_ptr<OrthographicCamera>& camera);

	void beginScene();
	void endScene();

	void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& colour);
	void drawQuad(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture);
	void drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture);
	void drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& colour);
	void drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const glm::vec4& colour);

    void drawQuad(const glm::vec2& pos, const glm::vec2& size, const std::array<glm::vec4, 4>& cols);
    void drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::array<glm::vec4, 4>& cols);
	void drawLine(const glm::vec2& start, const glm::vec2& end, float thickness, const glm::vec4& colour);

	void flush();

public:
    static const uint32_t MAX_QUADS = 20000;
    static const uint32_t MAX_VERTICIES = MAX_QUADS * 4;
    static const uint32_t MAX_INDICIES = MAX_QUADS * 6;
    static const uint32_t MAX_TEXTURES = 32;
    static const uint32_t QUAD_VERTEX_COUNT = 4;

private:
	void init();
    glm::mat4 calculateTransform(const glm::vec2& pos, const glm::vec2& size, float rotation);
    int addTexture(const std::shared_ptr<Texture2D>& texture);
    void drawVertex(const uint32_t num, const glm::mat4& transform, const glm::vec4& colour, int texIndex);
    void reset();
	void shutdown();

private:
    static const int32_t NO_TEXTURE_INDEX = -1;

    std::shared_ptr<OrthographicCamera> camera;

	std::shared_ptr<VertexBuffer> vertBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
	std::shared_ptr<Shader> shader;

	std::array<std::shared_ptr<Texture2D>, MAX_TEXTURES> textureSlots;
    uint32_t nextTextureSlotFree;

	uint32_t indexCount = 0;
	uint32_t quadCount = 0;

	struct VertexData
	{
		glm::vec2 position;
		int texIndex;
		glm::vec2 texCoord;
		glm::vec4 colour;
	};

	std::unique_ptr<std::array<VertexData, MAX_VERTICIES>> quadVertexBuffer;
    VertexData* quadVertexBufferPtr;

    const std::string RENDERER_2D_SHADER_SRC =
        "#type vertex\n"
        "#version 450 core\n"
        "layout(location = 0) in vec2 position;\n"
        "layout(location = 1) in int texIndex;\n"
        "layout(location = 2) in vec2 texCoord;\n"
        "layout(location = 3) in vec4 colour;\n"
        "out FRAG_INFO\n"
        "{\n"
        "    flat int texIndex;\n"
        "    vec2 texCoord;\n"
        "    vec4 colour;\n"
        "} fragInfo;\n"
        "uniform mat4 VP;\n"
        "void main()\n"
        "{\n"
        "    fragInfo.texIndex = texIndex;\n"
        "    fragInfo.texCoord = texCoord;\n"
        "    fragInfo.colour = colour;\n"
        "    gl_Position = VP * vec4(position, 0.0, 1.0);\n"
        "}\n"
        "#type fragment\n"
        "#version 450 core\n"
        "in FRAG_INFO\n"
        "{\n"
        "    flat int texIndex;\n"
        "    vec2 texCoord;\n"
        "    vec4 colour;\n"
        "} fragInfo;\n"
        "out vec4 fragColour;\n"
        "uniform sampler2D[32] textureSamplers;\n"
        "void main()\n"
        "{\n"
        "    fragColour = fragInfo.colour;\n"
        "    if(fragInfo.texIndex >= 0) fragColour *= texture(textureSamplers[fragInfo.texIndex],  fragInfo.texCoord);\n"
        "}\n";
};

