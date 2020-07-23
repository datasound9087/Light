#pragma once

#include "Font.h"

class FontLibrary
{
public:
	void addFont(const std::shared_ptr<Font>& font);
	std::shared_ptr<Font>& getFont(const std::string& name);
	bool exists(const std::string& name);

private:
	std::unordered_map<std::string, std::shared_ptr<Font>> fontLibrary;
};

