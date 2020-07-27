#include "lbpch.h"
#include "GLFrameBuffer.h"

#include <glad/glad.h>

GLFrameBuffer::GLFrameBuffer(const FrameBufferProps& props)
{
	this->props = props;
	rebuild();
}

GLFrameBuffer::~GLFrameBuffer()
{
	cleanup();
}

void GLFrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	GLint currentViewport[4];
	glGetIntegerv(GL_VIEWPORT, currentViewport);
	backupX = currentViewport[0];
	backupY = currentViewport[1];
	backupWidth = currentViewport[2];
	backupHeight = currentViewport[3];

	glViewport(0, 0, props.width, props.height);
}

void GLFrameBuffer::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(backupX, backupY, backupWidth, backupHeight);
}

void GLFrameBuffer::onResize(uint32_t width, uint32_t height)
{
	props.width = width;
	props.height = height;
	rebuild();
}

void GLFrameBuffer::setFrameBufferProps(const FrameBufferProps& props)
{
	this->props = props;
	rebuild();
}

const uint32_t GLFrameBuffer::getColourAttachmentID() const
{
	return colourAttachmentId;
}

const uint32_t GLFrameBuffer::getDepthStencilAttachmentID() const
{
	if (!props.hasDepthStencilAttachment)
		ERROR("FrameBuffer: No attatched depth texture");

	return depthStencilAttachmentId;
}

void GLFrameBuffer::bindColourAttachment(uint32_t slot)
{
	glBindTexture(GL_TEXTURE_2D, slot);
}

void GLFrameBuffer::bindDepthStencilAttachment(uint32_t slot)
{
	if (!props.hasDepthStencilAttachment)
		ERROR("FrameBuffer: No attatched depth texture");

	glBindTexture(GL_TEXTURE_2D, slot);
}

void GLFrameBuffer::rebuild()
{
	if (id) cleanup();

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	glCreateTextures(GL_TEXTURE_2D, 1, &colourAttachmentId);
	glBindTexture(GL_TEXTURE_2D, colourAttachmentId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, props.width, props.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colourAttachmentId, 0);

	if (props.hasDepthStencilAttachment)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &depthStencilAttachmentId);
		glBindTexture(GL_TEXTURE_2D, depthStencilAttachmentId);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, props.width, props.height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencilAttachmentId, 0);
	}

	ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "GL Framebuffer incomplete");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFrameBuffer::cleanup()
{
	glDeleteFramebuffers(1, &id);

	glDeleteTextures(1, &colourAttachmentId);
	if (props.hasDepthStencilAttachment)
		glDeleteTextures(1, &depthStencilAttachmentId);
}
