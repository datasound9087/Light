#include "lbpch.h"
#include "CameraLayer.h"

CameraLayer::CameraLayer(const std::string& name, const std::shared_ptr<ICamera>& camera, bool canMove, bool canRotate, bool canScroll)
	: Layer(name),
	camController(std::make_unique<CameraController>(camera, canMove, canRotate, canScroll))
{
}

void CameraLayer::onLayerEvent(const std::shared_ptr<event::Event>& evt)
{
	if (evt->getEventType() == event::EventType::WindowResized)
	{
		camController->onResize(std::static_pointer_cast<event::WindowResizedEvent>(evt));
	}

	onEvent(evt);
}

void CameraLayer::layerUpdate()
{
	update();
	camController->update();
}
