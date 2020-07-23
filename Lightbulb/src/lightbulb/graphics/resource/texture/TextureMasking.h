#pragma once

struct TextureMasking
{
	enum class Type
	{
		None = 0,
		SwizzleRedAlpha
	};

	Type type;

	TextureMasking(const Type& type = Type::None)
		: type(type)
	{}
};
