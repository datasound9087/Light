#pragma once
#include "lightbulb/graphics/DataTypes.h"

struct BufferElement
{
	std::string name;
	DataTypes::Types type;
	uint32_t size;
	uint32_t numPerVertex;
	size_t offset;
	bool normalised;

	BufferElement(const std::string& name, const DataTypes::Types& type, bool normalised = false)
		: name(name), type(type), offset(0), normalised(normalised)
	{
		this->numPerVertex = DataTypes::getComponentCount(type);
		this->size = DataTypes::getSize(type);
	}
};
