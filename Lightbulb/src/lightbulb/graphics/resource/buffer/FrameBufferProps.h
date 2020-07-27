#pragma once

#include "lbpch.h"

struct FrameBufferProps
{
	uint32_t width;
	uint32_t height;

	bool hasDepthStencilAttachment;

	FrameBufferProps(uint32_t width, uint32_t height)
		: width(width), height(height), hasDepthStencilAttachment(false)
	{}

	FrameBufferProps()
		: width(0), height(0), hasDepthStencilAttachment(false)
	{}
};