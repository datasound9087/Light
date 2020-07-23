#include "lbpch.h"
#include "FontLibrary.h"

void FontLibrary::addFont(const std::shared_ptr<Font>& font)
{
	if (!exists(font->getName()))
		fontLibrary[font->getName()] = font;
}

std::shared_ptr<Font>& FontLibrary::getFont(const std::string& name)
{
	if (exists(name))
		return fontLibrary[name];
}

bool FontLibrary::exists(const std::string& name)
{
	return fontLibrary.count(name) > 0;
}
