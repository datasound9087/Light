#pragma once

struct TextureFormat
{
	enum class Type
	{
		RGB = 0,
		RGBA,
		RED,
		RG
	};

	Type internalFormat;
	Type format;

	TextureFormat(const Type& format = Type::RGBA)
		: internalFormat(format), format(format)
	{}

	void setFormat(const Type& type)
	{
		internalFormat = type;
		format = type;
	}
};
