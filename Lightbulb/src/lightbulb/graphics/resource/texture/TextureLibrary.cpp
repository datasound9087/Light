#include "lbpch.h"
#include "TextureLibrary.h"

void TextureLibrary::addTexture(const std::shared_ptr<Texture>& texture)
{
	if (!exists(texture->getName()))
		textureLibrary[texture->getName()] = texture;
	
}

std::shared_ptr<Texture>& TextureLibrary::getTexture(const std::string& name)
{
	if (exists(name))
		return textureLibrary[name];
}

bool TextureLibrary::exists(const std::string& name)
{
	return textureLibrary.count(name) > 0;
}
