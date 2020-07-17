#pragma once
#include "lbpch.h"
#include "Glyph.h"
#include "lightbulb/graphics/resource/texture/Texture2D.h"
class Font
{
public:
	Font();
	~Font();

	const std::string& getName() const { return name; }
	uint32_t getSize() const { return size; }
	std::shared_ptr<Texture2D> getAtlas() { return textureAtlas; }

private:
	void init();

public:
	static const std::string LOCALE_EN;
	static const std::string NUMBERS;
	static const std::string SYMBOLS;

private:
	std::string name;
	uint32_t size;

	std::shared_ptr<Texture2D> textureAtlas;
	std::unordered_map<unsigned long, Glyph> glyphMap;
};

