#include "lbpch.h"
#include "Font.h"

#include <ftgl/freetype-gl.h>

const std::string Font::LOCALE_EN = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string Font::NUMBERS = "1234567890";
const std::string Font::SYMBOLS = "-=!\"£$%^&*()_+\\|`¬[]{};'#:@~,./<>?";

std::shared_ptr<Font> Font::create(const std::string& fontFile, uint32_t size, const std::string& locale)
{
	return std::make_shared<Font>(fontFile, size, locale);
}

Font::Font(const std::string& fontFile, uint32_t size, const std::string& locale)
	: size(size)
{
	init(fontFile, size, locale);
}

Font::~Font()
{
}

const Glyph& Font::getGlyph(unsigned long codePoint)
{
	return glyphMap[codePoint];
}

void Font::init(const std::string& fontFile, uint32_t size, const std::string& locale)
{
	const uint32_t WIDTH = 1920;
	const uint32_t HEIGHT = 1080;
	const uint32_t DEPTH = 1;
	ftgl::texture_atlas_t* ftTexAtlas = ftgl::texture_atlas_new(WIDTH, HEIGHT, DEPTH);
	ftgl::texture_font_t* ftTexFont = ftgl::texture_font_new_from_file(ftTexAtlas, size, fontFile.c_str());

	ftgl::texture_font_load_glyphs(ftTexFont, locale.c_str());
	ftgl::texture_font_load_glyphs(ftTexFont, NUMBERS.c_str());
	ftgl::texture_font_load_glyphs(ftTexFont, SYMBOLS.c_str());

	cacheGlyphs(ftTexFont, locale);
	cacheGlyphs(ftTexFont, NUMBERS);
	cacheGlyphs(ftTexFont, SYMBOLS);

	TextureProps props;
	props.format.setFormat(TextureFormat::Type::RED);
	props.filtering.setFilters(TextureFiltering::Type::Linear);
	props.wrapping.type = TextureWrapping::Type::ClampEdge;
	props.mask = TextureMasking::Type::SwizzleRedAlpha;
	
	textureAtlas = Texture2D::create(fontFile + std::to_string(size), WIDTH, HEIGHT, ftTexAtlas->data, props);

	ftgl::texture_atlas_delete(ftTexAtlas);
	ftgl::texture_font_delete(ftTexFont);
}

void Font::cacheGlyphs(ftgl::texture_font_t* font, const std::string& str)
{
	for (const auto& character : str)
	{
		ftgl::texture_glyph_t* ftGlyph = ftgl::texture_font_get_glyph(font, &character);

		Glyph glyph;
		glyph.codePoint = ftGlyph->codepoint;
		glyph.bearing = glm::ivec2(ftGlyph->offset_x, ftGlyph->offset_y);
		glyph.advance = glm::ivec2(ftGlyph->advance_x, ftGlyph->advance_y);
		glyph.size = glm::ivec2(ftGlyph->width, ftGlyph->height);

		//top left, top right, bot right, bot left
		glyph.texCoord[0] = glm::vec2(ftGlyph->s0, ftGlyph->t0);
		glyph.texCoord[1] = glm::vec2(ftGlyph->s1, ftGlyph->t0);
		glyph.texCoord[2] = glm::vec2(ftGlyph->s1, ftGlyph->t1);
		glyph.texCoord[3] = glm::vec2(ftGlyph->s0, ftGlyph->t1);

		glyphMap[character] = glyph;
	}
}
