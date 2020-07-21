#include "lbpch.h"
#include "RendererAPI.h"

#include "platform/opengl/GLRendererAPI.h"

#ifdef API_OPENGL
	RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;
#else
	#error "Not yet supported"
#endif

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