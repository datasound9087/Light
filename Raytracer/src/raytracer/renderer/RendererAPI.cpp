#include "rtpch.h"
#include "RendererAPI.h"

#include "platform/opengl/GLRendererAPI.h"

RendererAPI::API RendererAPI::api = RendererAPI::API::OPENGL;

std::unique_ptr<RendererAPI> RendererAPI::create()
{
	switch (api)
	{
	case RendererAPI::API::NONE:
		ASSERT(false, "Invalid API: None");
		return nullptr;
	case RendererAPI::API::OPENGL:
		return std::make_unique<GLRendererAPI>();
	}
}