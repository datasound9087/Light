#pragma once
#include "Texture.h"
class Texture2D : public Texture
{
public:
	static std::shared_ptr<Texture2D> create(const std::string& name, const std::string& path, bool flipOnLoad = false,
		const TextureProps& props = TextureProps());
	static std::shared_ptr<Texture2D> create(const std::string& name, int width, int height, const TextureProps& props = TextureProps());
};

