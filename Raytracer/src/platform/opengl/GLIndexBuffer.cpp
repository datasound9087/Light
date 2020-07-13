#include "rtpch.h"
#include "GLIndexBuffer.h"

GLIndexBuffer::GLIndexBuffer(uint32_t count, uint32_t* data)
{
	this->count = count;
	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

GLIndexBuffer::~GLIndexBuffer()
{
	glDeleteBuffers(1, &id);
}

void GLIndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void GLIndexBuffer::unBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
