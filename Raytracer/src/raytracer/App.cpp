#include "rtpch.h"
#include "App.h"
#include "raytracer/event/EventDispatcher.h"
#include "raytracer/renderer/RenderCommands.h"

App::App()
{
	INFO("Started");
	window = Window::create();
	eventHandler = window->getEventHandler();
}

void App::run()
{
	init();
	while (running)
	{
		handleEvents();
		render();
	}

	shutdown();
}

void App::init()
{
	std::array<float, 12> vertexData = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f
	};
	testVertexBuffer = VertexBuffer::create(DataTypes::Types::Float, vertexData.size(), vertexData.data(), VertexBuffer::Usage::STATIC);

	std::array<uint32_t, 6> indexData = {
		0, 1, 2,   
		0, 2, 3    
	};

	BufferElement positions("position", DataTypes::Types::Float, 3);
	BufferLayout layout;
	layout.addBufferElement(positions);
	testIndexBuffer = IndexBuffer::create(indexData.size(), indexData.data());
	
	testShader = Shader::create("test", "C:\\Users\\Sam\\source\\repos\\Raytracer\\Raytracer\\assets\\shaders\\test.glsl");
	testShader->setBufferLayout(layout);
	RenderCommands::setClearColour(glm::vec4(0.0f));
}

void App::render()
{
	RenderCommands::clear();
	testVertexBuffer->bind();
	testIndexBuffer->bind();
	testShader->bind();

	RenderCommands::drawIndexed(testIndexBuffer->getCount());
}

void App::handleEvents()
{
	window->onUpdate();
	while (eventHandler->hasEvents())
	{
		std::unique_ptr<event::Event> evt = eventHandler->nextEvent();
		event::EventDispatcher dispatcher(evt);
		dispatcher.dispatch<event::WindowClosedEvent>(EVENT_BIND_FUNC(App::onWindowClose));
		dispatcher.dispatch<event::WindowResizedEvent>(EVENT_BIND_FUNC(App::onWindowResize));
	}
}

void App::onWindowClose(std::unique_ptr<event::WindowClosedEvent>& evt)
{
	INFO("Running");
	running = false;
}

void App::onWindowResize(std::unique_ptr<event::WindowResizedEvent>& evt)
{
	INFO("Resizing!");
	RenderCommands::setViewport(0, 0, evt->getWidth(), evt->getHeight());
}

void App::shutdown()
{
	//if running in debug mode and having console pause to read log
#if CONFIG_DEBUG
	window->shutdown();
#endif
}
