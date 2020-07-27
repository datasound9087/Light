#pragma once

#include "lightbulb/graphics/resource/buffer/FrameBuffer.h"

class GLFrameBuffer : public FrameBuffer
{
public:
	GLFrameBuffer(const FrameBufferProps& props);
	virtual ~GLFrameBuffer();

	void bind() override;
	void unBind() override;

	void onResize(uint32_t width, uint32_t height) override;

	void setFrameBufferProps(const FrameBufferProps& props) override;

	const uint32_t getColourAttachmentID() const override;
	const uint32_t getDepthStencilAttachmentID() const override;

	void bindColourAttachment(uint32_t slot) override;
	void bindDepthStencilAttachment(uint32_t slot) override;

private:
	void rebuild();
	void cleanup();

private:
	uint32_t id;
	uint32_t colourAttachmentId;
	uint32_t depthStencilAttachmentId;
};

