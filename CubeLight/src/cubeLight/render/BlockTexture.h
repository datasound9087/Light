#pragma once

#include "lbpch.h"
#include "lightbulb/util/Side.h"

class BlockTexture
{
public:
	enum class Mapping
	{
		ALL = 0,
		FRONT,
		TOP_SIDE_BOTTOM
	};

public:
	BlockTexture(const std::string& name, const Mapping& mapping);
	
	const std::string& getTextureForSide(Side side);

private:
	void calcMappings(const Mapping& mapping);
	void mapAll();
	void mapFront();
	void mapTopSideBottom();

private:
	std::string name;
	Mapping mapping;
	std::unordered_map<Side, std::string> textureSideMap;
};

