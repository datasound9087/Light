#include "lbpch.h"
#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::shared_ptr<Texture2D>& texture, const AtlasLayout& layout)
	: texture(texture), layout(layout)
{
	calcTexCoords();
}

void TextureAtlas::setLayout(const AtlasLayout& layout)
{
	this->layout = layout;
	calcTexCoords();
}

const std::array<glm::vec2, 4> TextureAtlas::getCoordsOf(const std::string& name)
{
	if (layout.elements.count(name) == 0)
	{
		ERROR("Cannot find {0} in AtlsLayout", name);
	}
	return layout.elements.at(name).texCoords;
}

void TextureAtlas::calcTexCoords()
{
	float ratioX = 1.0f / texture->getWidth();
	float ratioY = 1.0f / texture->getHeight();
	for (auto& group : layout.elements)
	{
		group.second.calcTexCoords(ratioX, ratioY);
	}
}
