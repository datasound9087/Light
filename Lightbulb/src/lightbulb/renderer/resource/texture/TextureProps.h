#pragma once
#include "TextureWrapping.h"
#include "TextureFiltering.h"
#include "TextureFormat.h"

struct TextureProps
{
	TextureWrapping wrapping;
	TextureFiltering filtering;
	TextureFormat format;
	bool genMipmaps;

	TextureProps(const TextureWrapping& wrap = TextureWrapping(), const TextureFiltering& filtering = TextureFiltering(),
		const TextureFormat& format = TextureFormat(), bool genMipmaps = false)
		: wrapping(wrap), filtering(filtering), format(format), genMipmaps(genMipmaps)
	{}
};