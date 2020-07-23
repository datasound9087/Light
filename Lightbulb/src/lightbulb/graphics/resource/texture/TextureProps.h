#pragma once
#include "TextureWrapping.h"
#include "TextureFiltering.h"
#include "TextureFormat.h"
#include "TextureMasking.h"

struct TextureProps
{
	TextureWrapping wrapping;
	TextureFiltering filtering;
	TextureFormat format;
	TextureMasking mask;
	bool genMipmaps;

	TextureProps(const TextureWrapping& wrap = TextureWrapping(), const TextureFiltering& filtering = TextureFiltering(),
		const TextureFormat& format = TextureFormat(), const TextureMasking& mask = TextureMasking(), bool genMipmaps = false)
		: wrapping(wrap), filtering(filtering), format(format), genMipmaps(genMipmaps), mask(mask)
	{}
};