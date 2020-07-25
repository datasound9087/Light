#pragma once

#include "AtlasLayout.h"
#include "lightbulb/graphics/resource/texture/Texture2D.h"

class TextureAtlas
{
public:
	TextureAtlas(const std::shared_ptr<Texture2D>& texture, const AtlasLayout& layout);

	void setLayout(const AtlasLayout& layout);
	const AtlasLayout& getLayout() const { return layout; }

	const std::array<glm::vec2, 4> getCoordsOf(const std::string& name);

private:
	void calcTexCoords();

private:
	std::shared_ptr<Texture2D> texture;
	AtlasLayout layout;
};

