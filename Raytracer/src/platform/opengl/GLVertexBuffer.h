#pragma once
#include <glad/glad.h>
#include "raytracer/renderer/resource/buffer/VertexBuffer.h"

class GLVertexBuffer : public VertexBuffer
{
public:
	GLVertexBuffer(const DataTypes::Types& type, size_t size, const VertexBuffer::Usage& usage);
	GLVertexBuffer(const DataTypes::Types& type, size_t size, void* data, const Usage& usage);
	virtual ~GLVertexBuffer();
	void bind() override;
	void unBind() override;
	virtual void setData(const std::unique_ptr<void>& data, size_t size) override;

private:
	GLuint id;
};

