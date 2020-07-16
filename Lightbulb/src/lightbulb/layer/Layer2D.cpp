#include "lbpch.h"
#include "Layer2D.h"
#include "lightbulb/graphics/RenderCommands.h"
#include "lightbulb/event/WindowEvents.h"

Layer2D::Layer2D(const std::string& name, int width, int height)
	: Layer(name)
{
	camera = std::make_shared<OrthographicCamera>(0, width, 0, height);
	renderer = std::make_unique<Renderer2D>(camera);
}

Layer2D::~Layer2D()
{
}

void Layer2D::onLayerEvent(const std::shared_ptr<event::Event>& evt)
{
	if (evt->getEventType() == event::EventType::WindowResized)
	{
		auto windowResizeEvt = std::static_pointer_cast<event::WindowResizedEvent>(evt);
		camera->setView(0, windowResizeEvt->getWidth(), 0, windowResizeEvt->getHeight());
	}

	onEvent(evt);
}

void Layer2D::renderLayer()
{
	renderer->beginScene();
	render();
	renderer->endScene();
	renderer->flush();
}