#pragma once
#include "Texture.h"

class TextureLibrary
{
public:
	void addTexture(const std::shared_ptr<Texture>& texture);
	std::shared_ptr<Texture>& getTexture(const std::string& name);
	bool exists(const std::string& name);

private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> textureLibrary;
};

