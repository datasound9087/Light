#include "lbpch.h"
#include "IndexBuffer.h"
#include "lightbulb/graphics/RendererAPI.h"
#include "platform/opengl/GLIndexBuffer.h"

std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t count, uint32_t* data)
{
	switch(RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return std::make_shared<GLIndexBuffer>(count, data);
	}
}
