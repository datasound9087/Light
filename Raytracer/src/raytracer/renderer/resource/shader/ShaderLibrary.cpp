#include "rtpch.h"
#include "ShaderLibrary.h"

void ShaderLibrary::addShader(const std::shared_ptr<Shader>& shader)
{
	if (!exists(shader->getName()))
		shaderLibrary[shader->getName()] = shader;
}

std::shared_ptr<Shader>& ShaderLibrary::getShader(const std::string& name)
{
	if (exists(name))
		return shaderLibrary[name];
}

bool ShaderLibrary::exists(const std::string& name)
{
	return shaderLibrary.count(name) > 0;
}
