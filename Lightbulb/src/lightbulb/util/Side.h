#pragma once

enum class Side
{
	FRONT = 0,
	LEFT,
	BACK,
	RIGHT,
	TOP,
	BOTTOM
};

namespace Sides
{
	const std::string& toString(const Side& side)
	{
		switch (side)
		{
		case Side::FRONT: return ":front";
		case Side::BACK: return ":back";
		case Side::LEFT: return ":left";
		case Side::RIGHT: return ":right";
		case Side::TOP: return ":top";
		case Side::BOTTOM: return ":bottom";
		}
	}
}
