#include "lbpch.h"
#include "GLVertexBuffer.h"

GLVertexBuffer::GLVertexBuffer(const DataTypes::Types& type, size_t size, const VertexBuffer::Usage& usage)
{
	this->type = type;
	this->size = size;
	this->usage = usage;

	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ARRAY_BUFFER, DataTypes::getSize(type) * size, nullptr, usage == VertexBuffer::Usage::STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

GLVertexBuffer::GLVertexBuffer(const DataTypes::Types& type, size_t size, void* data, const Usage& usage)
{
	this->type = type;
	this->size = size;
	this->usage = usage;

	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ARRAY_BUFFER, DataTypes::getSize(type) * size, data, usage == VertexBuffer::Usage::STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

GLVertexBuffer::GLVertexBuffer(size_t size, const Usage& usage)
{
	this->type = DataTypes::Types::None;
	this->size = size;
	this->usage = usage;

	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage == VertexBuffer::Usage::STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &id);
}

void GLVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void GLVertexBuffer::unBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::setData(const void* data, size_t size)
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
