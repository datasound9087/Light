#include "BlockTexture.h"

BlockTexture::BlockTexture(const std::string& name, const Mapping& mapping)
	: name(name), mapping(mapping)
{
}

const std::string& BlockTexture::getTextureForSide(Side side)
{
	return textureSideMap[side];
}

void BlockTexture::calcMappings(const Mapping& mapping)
{
	switch (mapping)
	{
	case Mapping::ALL:
		mapAll();
		break;
	case Mapping::FRONT:
		mapFront();
		break;
	case Mapping::TOP_SIDE_BOTTOM:
		mapTopSideBottom();
		break;
	default:
		ERROR("invalid block texture mapping");
	}
}

void BlockTexture::mapAll()
{
	textureSideMap[Side::FRONT] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::BACK] = name + Sides::toString(Side::BACK);
	textureSideMap[Side::LEFT] = name + Sides::toString(Side::LEFT);
	textureSideMap[Side::RIGHT] = name + Sides::toString(Side::RIGHT);
	textureSideMap[Side::TOP] = name + Sides::toString(Side::TOP);
	textureSideMap[Side::BOTTOM] = name + Sides::toString(Side::BOTTOM);
}

void BlockTexture::mapFront()
{
	textureSideMap[Side::FRONT] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::BACK] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::LEFT] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::RIGHT] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::TOP] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::BOTTOM] = name + Sides::toString(Side::FRONT);
}

void BlockTexture::mapTopSideBottom()
{
	textureSideMap[Side::FRONT] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::BACK] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::LEFT] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::RIGHT] = name + Sides::toString(Side::FRONT);
	textureSideMap[Side::TOP] = name + Sides::toString(Side::TOP);
	textureSideMap[Side::BOTTOM] = name + Sides::toString(Side::BOTTOM);
}
