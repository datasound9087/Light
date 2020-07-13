#include "rtpch.h"
#include "Shader.h"
#include "raytracer/renderer/RendererAPI.h"
#include "platform/opengl/GLShader.h"

std::shared_ptr<Shader> Shader::create(const std::string& name, const std::string& path)
{
	switch (RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return std::make_shared<GLShader>(name, path);
	}
}

std::shared_ptr<Shader> Shader::create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc, const std::string& geomSrc)
{
	switch (RendererAPI::getAPI())
	{
	case RendererAPI::API::None:
		ASSERT(false, "Invalid API: None");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return std::make_shared<GLShader>(name, vertSrc, fragSrc, geomSrc);
	}
}
