#pragma once

#include "lightbulb/graphics/RendererAPI.h"

class GLRendererAPI : public RendererAPI
{
public:
	virtual ~GLRendererAPI() {}
	void init() override;

	void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	void setClearColour(const glm::vec4& colour) override;
	void clear() override;
	void drawIndexed(uint32_t count) override;
	void drawArrays(const DrawType& type, uint32_t count) override;
};

