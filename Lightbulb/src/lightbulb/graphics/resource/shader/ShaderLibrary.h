#pragma once
#include "Shader.h"

class ShaderLibrary
{
public:
	void addShader(const std::shared_ptr<Shader>& shader);
	std::shared_ptr<Shader>& getShader(const std::string& name);
	bool exists(const std::string& name);

private:
	std::unordered_map<std::string, std::shared_ptr<Shader>> shaderLibrary;
};

