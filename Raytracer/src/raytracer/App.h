#pragma once

#include "raytracer/core/Window.h"
#include "raytracer/event/WindowEvents.h"
#include "raytracer/renderer/resource/buffer/VertexBuffer.h"
#include "raytracer/renderer/resource/buffer/IndexBuffer.h"
#include "raytracer/renderer/resource/shader/Shader.h"

class App
{
public:
	App();
	void run();

private:
	
	void init();
	void render();
	void handleEvents();
	void onWindowClose(std::unique_ptr<event::WindowClosedEvent>& evt);
	void onWindowResize(std::unique_ptr<event::WindowResizedEvent>& evt);
	void shutdown();

private:
	std::unique_ptr<Window> window;
	std::shared_ptr<VertexBuffer> testVertexBuffer;
	std::shared_ptr<IndexBuffer> testIndexBuffer;
	std::shared_ptr<Shader> testShader;
	std::shared_ptr<event::EventBuffer> eventHandler;
	bool running = true;
};

