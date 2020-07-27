#include "lbpch.h"
#include "FrameBuffer.h"
#include "lightbulb/graphics/RendererAPI.h"

#include "platform/opengl/GLFrameBuffer.h"

std::shared_ptr<FrameBuffer> FrameBuffer::create(const FrameBufferProps& props)
{
	switch (RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return std::make_shared<GLFrameBuffer>(props);
	}
}
