#pragma once

#include <glm/vec4.hpp>

struct TextureWrapping
{
	enum class Type
	{
		Repeat = 0,
		MirroredRepeat,
		ClampEdge,
		ClampBorder
	};

	Type type;
	glm::vec4 borderCol;

	TextureWrapping(const Type& type = Type::MirroredRepeat)
		: type(type), borderCol(1.0f)
	{}
};