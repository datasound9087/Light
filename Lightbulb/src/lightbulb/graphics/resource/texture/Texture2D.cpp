#include "lbpch.h"
#include "Texture2D.h"
#include "lightbulb/renderer/RendererAPI.h"
#include "platform/opengl/GLTexture2D.h"

std::shared_ptr<Texture2D> Texture2D::create(const std::string& name, const std::string& path, bool flipOnLoad, const TextureProps& props)
{
	switch (RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return std::make_shared<GLTexture2D>(name, path, flipOnLoad, props);
	}
}

std::shared_ptr<Texture2D> Texture2D::create(const std::string& name, int width, int height, const TextureProps& props)
{
	switch (RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;
	case RendererAPI::API::OpenGL:
		return std::make_shared<GLTexture2D>(name, width, height, props);
	}
}
