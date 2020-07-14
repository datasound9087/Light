#include "lbpch.h"
#include "VertexBuffer.h"
#include "lightbulb/renderer/RendererAPI.h"
#include "platform/opengl/GLVertexBuffer.h"

std::shared_ptr<VertexBuffer> VertexBuffer::create(const DataTypes::Types& type, size_t size, const Usage& usage)
{
	switch (RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return std::make_shared<GLVertexBuffer>(type, size, usage);
	}
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(size_t size, const Usage& usage)
{
	switch (RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return std::make_shared<GLVertexBuffer>(size, usage);
	}
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(const DataTypes::Types& type, size_t size, void* data, const Usage& usage)
{
	switch (RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return std::make_shared<GLVertexBuffer>(type, size, data, usage);
	}
}
