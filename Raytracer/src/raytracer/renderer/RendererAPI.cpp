#include "rtpch.h"
#include "RendererAPI.h"

#include "platform/opengl/GLRendererAPI.h"

RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;

std::unique_ptr<RendererAPI> RendererAPI::create()
{
	switch (api)
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return std::make_unique<GLRendererAPI>();
	}
}