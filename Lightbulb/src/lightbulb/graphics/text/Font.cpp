#include "lbpch.h"
#include "Font.h"

#include <ftgl/freetype-gl.h>

const std::string Font::LOCALE_EN = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string Font::NUMBERS = "1234567890";
const std::string Font::SYMBOLS = "-=!\"£$%^&*()_+\\|`¬[]{};'#:@~,./<>?";

Font::Font(const std::string& fontFile, uint32_t size, const std::string& locale)
	: size(size)
{
	init(fontFile, size, locale);
}

Font::~Font()
{
}

void Font::init(const std::string& fontFile, uint32_t size, const std::string& locale)
{
}
