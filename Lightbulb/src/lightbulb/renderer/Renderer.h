#pragma once

#include "RendererAPI.h"

class Renderer
{
public:
	static void init();
	static void shutdown();

	static void onWindowResize(uint32_t width, uint32_t height);

	static RendererAPI::API getAPI() { return RendererAPI::getAPI();  }
};

