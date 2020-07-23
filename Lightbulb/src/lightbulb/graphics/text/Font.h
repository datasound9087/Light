#pragma once
#include "Glyph.h"
#include "lightbulb/graphics/resource/texture/Texture2D.h"

namespace ftgl
{
	struct texture_font_t;
}

class Font
{
public:
	static std::shared_ptr<Font> create(const std::string& fontFile, uint32_t size, const std::string& locale = LOCALE_EN);
	Font(const std::string& fontFile, uint32_t size, const std::string& locale);
	~Font();

	const std::string& getName() const { return name; }
	uint32_t getSize() const { return size; }

	const Glyph& getGlyph(unsigned long codePoint);
	std::shared_ptr<Texture2D> getAtlas() { return textureAtlas; }

private:
	void init(const std::string& fontFile, uint32_t size, const std::string& locale);
	void cacheGlyphs(ftgl::texture_font_t* font, const std::string& str);
public:
	static const std::string LOCALE_EN;
	static const std::string NUMBERS;
	static const std::string SYMBOLS;

private:
	std::string name;
	uint32_t size;

	std::unordered_map<unsigned long, Glyph> glyphMap;
	std::shared_ptr<Texture2D> textureAtlas;
};

