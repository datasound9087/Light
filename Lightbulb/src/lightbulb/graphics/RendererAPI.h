#include "lbpch.h"

#include <glm/vec4.hpp>
#include "lightbulb/graphics/RenderDrawTypes.h"

#pragma once
class RendererAPI
{
public:
	enum class API
	{
		None = 0,
		OpenGL = 1
	};

public:
	static API getAPI() { return api; }
	static std::unique_ptr<RendererAPI> create();
	virtual ~RendererAPI() = default;
	virtual void init() = 0;

	virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
	virtual void setClearColour(const glm::vec4& colour) = 0;
	virtual void clear() = 0;
	virtual void drawIndexed(uint32_t count) = 0;
	virtual void drawArrays(const DrawType& type, uint32_t count) = 0;

private:
	static API api;
};

