#pragma once
#include "raytracer/renderer/DataTypes.h"

struct BufferElement
{
	std::string name;
	DataTypes::Types type;
	uint32_t size;
	uint32_t numPerVertex;
	size_t offset;
	bool normalised;

	BufferElement(const std::string& name, const DataTypes::Types& type, uint32_t numPerVertex, bool normalised = false)
		: name(name), type(type), numPerVertex(numPerVertex), offset(0), size(DataTypes::getSize(type) * numPerVertex), normalised(normalised)
	{}
};
