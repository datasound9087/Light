#include "lbpch.h"
#include "Font.h"

#include <ft2build.h>
#define FT_FREETYPE_H

const std::string Font::LOCALE_EN = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string Font::NUMBERS = "1234567890";
const std::string Font::SYMBOLS = "-=!\"£$%^&*()_+\\|`¬[]{};'#:@~,./<>?";

Font::Font()
{
}

Font::~Font()
{
}

void Font::init()
{
}
