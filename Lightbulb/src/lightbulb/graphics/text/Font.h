#pragma once
#include "lbpch.h"
#include "Glyph.h"
#include "lightbulb/graphics/resource/texture/Texture2D.h"

class Font
{
public:
	Font(const std::string& fontFile, uint32_t size, const std::string& locale = LOCALE_EN);
	~Font();

	const std::string& getName() const { return name; }
	uint32_t getSize() const { return size; }
	std::shared_ptr<Texture2D> getAtlas() { return textureAtlas; }

private:
	void init(const std::string& fontFile, uint32_t size, const std::string& locale);
public:
	static const std::string LOCALE_EN;
	static const std::string NUMBERS;
	static const std::string SYMBOLS;

private:
	std::string name;
	uint32_t size;

	std::shared_ptr<Texture2D> textureAtlas;
};

