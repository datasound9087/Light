#pragma once
#include <glad/glad.h>
#include "lightbulb/graphics/resource/buffer/IndexBuffer.h"

class GLIndexBuffer : public IndexBuffer
{
public:
	GLIndexBuffer(uint32_t count, uint32_t* data);
	virtual ~GLIndexBuffer();

	void bind() override;
	void unBind() override;

private:
	GLuint id;
};

