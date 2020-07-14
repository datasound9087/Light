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
	Renderer2D(const OrthographicCamera& camera);
	~Renderer2D();
	void setCamera(const OrthographicCamera& camera);

	void beginScene();
	void endScene();

	void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& colour);
	void drawQuad(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture);
	void drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture);
	void drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& colour);
	void drawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const glm::vec4& colour);

	void drawLine(const glm::vec2& start, const glm::vec2& end, float thickness, const glm::vec4& colour);

	void flush();
private:
	void init();
    float addTexture(const std::shared_ptr<Texture2D>& texture);
    void drawVertex(const uint32_t num, const glm::mat4& transform, const glm::vec2& colour, float texIndex);
    void reset();
	void shutdown();

private:
	OrthographicCamera camera;

	std::shared_ptr<VertexBuffer> vertBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
	std::shared_ptr<Shader> shader;

	static const uint32_t MAX_QUADS = 20000;
	static const uint32_t MAX_VERTICIES = MAX_QUADS * 4;
	static const uint32_t MAX_INDICIES = MAX_QUADS * 6;
	static const uint32_t MAX_TEXTURES = 32;

	std::array<std::shared_ptr<Texture2D>, MAX_TEXTURES> textureSlots;
    uint32_t nextTextureSlotFree;

	uint32_t indexCount = 0;
	uint32_t quadCount = 0;

	struct VertexData
	{
		glm::vec2 position;
		float texIndex;
		glm::vec2 texCoord;
		glm::vec4 colour;
	};

	std::unique_ptr<std::array<VertexData, MAX_VERTICIES>> quadVertexBuffer;
    VertexData* quadVertexBufferPtr;

    const std::string RENDERER_2D_SHADER_SRC =
        "#type vertex\n"
        "#version 450 core\n"
        "layout(location = 0) in vec2 position;\n"
        "layout(location = 1) in float texIndex;\n"
        "layout(location = 2) in vec2 texCoord;\n"
        "layout(location = 3) in vec4 colour;\n"
        "out fragInfo\n"
        "{\n"
        "    float texIndex;\n"
        "    vec2 texCoord;\n"
        "    vec4 colour;\n"
        "};\n"
        "uniform mat4 VP;\n"
        "void main()\n"
        "{\n"
        "    fragInfo.texIndex = texIndex;\n"
        "    fraginfo.texCoord = texCoord;\n"
        "    fragInfo.colour = colour;\n"
        "    gl_Position = VP * vec4(position, 0.0, 1.0);\n"
        "}\n"
        "#type fragment\n"
        "#version 450 core\n"
        "in fragInfo\n"
        "{\n"
        "    float texIndex;\n"
        "    vec2 texCoord;\n"
        "    vec4 colour;\n"
        "};\n"
        "out vec4 fragColour;\n"
        "uniform sampler2D[32] textureSamplers;\n"
        "void main()\n"
        "{\n"
        "    fragColour = colour;\n"
        "    switch (int(fragInfo.texIndex))\n"
        "    {\n"
        "    case 0:  fragColour *= texture(textureSamplers[0],  fragInfo.texCoord); break;\n"
        "    case 1:  fragColour *= texture(textureSamplers[1],  fragInfo.texCoord); break;\n"
        "    case 2:  fragColour *= texture(textureSamplers[2],  fragInfo.texCoord); break;\n"
        "    case 3:  fragColour *= texture(textureSamplers[3],  fragInfo.texCoord); break;\n"
        "    case 4:  fragColour *= texture(textureSamplers[4],  fragInfo.texCoord); break;\n"
        "    case 5:  fragColour *= texture(textureSamplers[5],  fragInfo.texCoord); break;\n"
        "    case 6:  fragColour *= texture(textureSamplers[6],  fragInfo.texCoord); break;\n"
        "    case 7:  fragColour *= texture(textureSamplers[7],  fragInfo.texCoord); break;\n"
        "    case 8:  fragColour *= texture(textureSamplers[8],  fragInfo.texCoord); break;\n"
        "    case 9:  fragColour *= texture(textureSamplers[9],  fragInfo.texCoord); break;\n"
        "    case 10: fragColour *= texture(textureSamplers[10], fragInfo.texCoord); break;\n"
        "    case 11: fragColour *= texture(textureSamplers[11], fragInfo.texCoord); break;\n"
        "    case 12: fragColour *= texture(textureSamplers[12], fragInfo.texCoord); break;\n"
        "    case 13: fragColour *= texture(textureSamplers[13], fragInfo.texCoord); break;\n"
        "    case 14: fragColour *= texture(textureSamplers[14], fragInfo.texCoord); break;\n"
        "    case 15: fragColour *= texture(textureSamplers[15], fragInfo.texCoord); break;\n"
        "    case 16: fragColour *= texture(textureSamplers[16], fragInfo.texCoord); break;\n"
        "    case 17: fragColour *= texture(textureSamplers[17], fragInfo.texCoord); break;\n"
        "    case 18: fragColour *= texture(textureSamplers[18], fragInfo.texCoord); break;\n"
        "    case 19: fragColour *= texture(textureSamplers[19], fragInfo.texCoord); break;\n"
        "    case 20: fragColour *= texture(textureSamplers[20], fragInfo.texCoord); break;\n"
        "    case 21: fragColour *= texture(textureSamplers[21], fragInfo.texCoord); break;\n"
        "    case 22: fragColour *= texture(textureSamplers[22], fragInfo.texCoord); break;\n"
        "    case 23: fragColour *= texture(textureSamplers[23], fragInfo.texCoord); break;\n"
        "    case 24: fragColour *= texture(textureSamplers[24], fragInfo.texCoord); break;\n"
        "    case 25: fragColour *= texture(textureSamplers[25], fragInfo.texCoord); break;\n"
        "    case 26: fragColour *= texture(textureSamplers[26], fragInfo.texCoord); break;\n"
        "    case 27: fragColour *= texture(textureSamplers[27], fragInfo.texCoord); break;\n"
        "    case 28: fragColour *= texture(textureSamplers[28], fragInfo.texCoord); break;\n"
        "    case 29: fragColour *= texture(textureSamplers[29], fragInfo.texCoord); break;\n"
        "    case 30: fragColour *= texture(textureSamplers[30], fragInfo.texCoord); break;\n"
        "    case 31: fragColour *= texture(textureSamplers[31], fragInfo.texCoord); break;\n"
        "    }\n"
        "}\n";
};

