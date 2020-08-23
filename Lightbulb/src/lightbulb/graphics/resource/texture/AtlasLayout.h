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
		addElement(name + Sides::toString(Side::FRONT), AtlasElement(position, size));
		addElement(name + Sides::toString(Side::LEFT), AtlasElement(glm::ivec2(position.x + (1 * size.x), position.y), size));
		addElement(name + Sides::toString(Side::RIGHT), AtlasElement(glm::ivec2(position.x + (2 * size.x), position.y), size));
		addElement(name + Sides::toString(Side::BACK), AtlasElement(glm::ivec2(position.x + (3 * size.x), position.y), size));
		addElement(name + Sides::toString(Side::TOP), AtlasElement(glm::ivec2(position.x + (4 * size.x), position.y), size));
		addElement(name + Sides::toString(Side::BOTTOM), AtlasElement(glm::ivec2(position.x + (5 * size.x), position.y), size));
	}

	const std::string getTexNameOfSide(std::string& name, const Side& side) const
	{
		std::string texName = name;
		switch (side)
		{
		case Side::FRONT:
			texName += Sides::toString(Side::FRONT);
			break;
		case Side::LEFT:
			texName += Sides::toString(Side::LEFT);
			break;
		case Side::BACK:
			texName += Sides::toString(Side::BACK);
			break;
		case Side::RIGHT:
			texName += Sides::toString(Side::RIGHT);
			break;
		case Side::TOP:
			texName += Sides::toString(Side::TOP);
			break;
		case Side::BOTTOM:
			texName += Sides::toString(Side::BOTTOM);
			break;
		}

		return texName;
	}
};
