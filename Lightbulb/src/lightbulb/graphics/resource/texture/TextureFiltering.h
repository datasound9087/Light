#pragma once

struct TextureFiltering
{
	enum class Type
	{
		Nearest = 0,
		Linear,
		MipmapNearestToNearest,
		MipmapLinearToNearest,
		MipmapNearestToLinear,
		MipmapLinearToLinear
	};

	Type maxFilter;
	Type minFilter;

	TextureFiltering(const Type& min = Type::Nearest, const Type& max = Type::Linear)
		: minFilter(min), maxFilter(max)
	{}
};