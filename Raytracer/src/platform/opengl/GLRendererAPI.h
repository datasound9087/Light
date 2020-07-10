#pragma once

#include "raytracer/renderer/RendererAPI.h"

class GLRendererAPI : public RendererAPI
{
public:
	virtual ~GLRendererAPI();
	void init() override;

	virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	virtual void setClearColour(const glm::vec4& colour) override;
	virtual void clear() override;
};

