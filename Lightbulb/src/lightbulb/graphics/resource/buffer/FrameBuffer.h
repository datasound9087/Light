#pragma once

#include "lightbulb/graphics/resource/IGPUResource.h"
#include "lightbulb/graphics/resource/buffer/FrameBufferProps.h"

class FrameBuffer : public IGPUResource
{
public:
	static std::shared_ptr<FrameBuffer> create(const FrameBufferProps& props);

public:
	virtual void onResize(uint32_t width, uint32_t  height) = 0;

	const FrameBufferProps& getFrameBufferProps() const { return props; }
	virtual void setFrameBufferProps(const FrameBufferProps& props) = 0;

	virtual const uint32_t getColourAttachmentID() const = 0;
	virtual const uint32_t getDepthStencilAttachmentID() const = 0;

	virtual void bindColourAttachment(uint32_t slot) = 0;
	virtual void bindDepthStencilAttachment(uint32_t slot) = 0;

protected:
	FrameBufferProps props;

	uint32_t backupX;
	uint32_t backupY;
	uint32_t backupWidth;
	uint32_t backupHeight;
};

