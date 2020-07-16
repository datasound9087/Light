#pragma once
#include "TextureProps.h"

class Texture
{
public:
	virtual ~Texture() = default;
	const int getWidth() const { return width; }
	const int getHeight() const { return height; }
	const std::string& getName() const { return name; }
	const TextureProps& getProps() const { return props; }

	virtual void bind(const uint32_t slot) = 0;
	virtual void unBnd() = 0;

protected:
	uint32_t width;
	uint32_t height;
	std::string name;
	TextureProps props;
};

