#pragma once
#include <glad/glad.h>
#include "lightbulb/graphics/resource/buffer/VertexBuffer.h"

class GLVertexBuffer : public VertexBuffer
{
public:
	GLVertexBuffer(const DataTypes::Types& type, size_t size, const VertexBuffer::Usage& usage);
	GLVertexBuffer(const DataTypes::Types& type, size_t size, void* data, const Usage& usage);
	GLVertexBuffer(size_t size, const Usage& usage);
	GLVertexBuffer(size_t size, void* data, const Usage& usage);
	virtual ~GLVertexBuffer();
	void bind() override;
	void unBind() override;
	virtual void setData(const void* data, size_t size) override;

private:
	GLuint id;
};

