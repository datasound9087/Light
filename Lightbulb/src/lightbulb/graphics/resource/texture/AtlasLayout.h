#pragma once

#include "AtlasElement.h"
#include "lightbulb/util/Side.h"

struct AtlasLayout
{
	std::unordered_map<std::string, AtlasElement> elements;

	void addElement(const std::string& name, const AtlasElement& elem)
	{
		elements.insert({ name, elem });
	}

	void addCubeElements(const std::string& name, glm::ivec2 position, glm::ivec2 size)
	{
		addElement(name + ":front", AtlasElement(position, size));
		addElement(name + ":left", AtlasElement(glm::ivec2(position.x + (1 * size.x), position.y), size));
		addElement(name + ":right", AtlasElement(glm::ivec2(position.x + (2 * size.x), position.y), size));
		addElement(name + ":back", AtlasElement(glm::ivec2(position.x + (3 * size.x), position.y), size));
		addElement(name + ":top", AtlasElement(glm::ivec2(position.x + (4 * size.x), position.y), size));
		addElement(name + ":bottom", AtlasElement(glm::ivec2(position.x + (5 * size.x), position.y), size));
	}

	const std::string getTexNameOfSide(std::string& name, const Side& side) const
	{
		std::string texName = name;
		switch (side)
		{
		case Side::FRONT: texName += ":front";
		case Side::LEFT: texName += ":left";
		case Side::BACK: texName += ":back";
		case Side::RIGHT: texName += ":right";
		case Side::TOP: texName += ":top";
		case Side::BOTTOM: texName += ":bottom";
		}

		return texName;
	}
};
