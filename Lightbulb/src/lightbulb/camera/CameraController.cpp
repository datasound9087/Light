#include "lbpch.h"
#include "CameraController.h"

#include "lightbulb/core/Input.h"
#include "lightbulb/event/Keys.h"
#include "lightbulb/event/EventDispatcher.h"

const float CameraController::DEFAULT_MOVEMENT_SPEED = 2.5f;
const float CameraController::DEFAULT_MOUSE_SENSITIVITY = 0.1f;
const float CameraController::DEFAULT_SCROLL_SENSITIVITY = 1.0f;

void CameraController::onEvent(const std::shared_ptr<event::Event>& evt)
{
	event::EventDispatcher e(evt);
	if(!locked && canRotate) e.dispatch<event::MouseMovedEvent>(EVENT_BIND_FUNC(CameraController::processMouseMove));
	if(!locked && canZoom) e.dispatch<event::MouseScrolledEvent>(EVENT_BIND_FUNC(CameraController::processMouseScroll));
}

void CameraController::update()
{
	if (!locked && canMove)
	{
		float velocity = movementSpeed;
		if (Input::isKeyPressed(input::KEY_W))
			camera->move(Direction::UP, velocity);

		else if (Input::isKeyPressed(input::KEY_S))
			camera->move(Direction::DOWN, velocity);

		if (Input::isKeyPressed(input::KEY_A))
			camera->move(Direction::LEFT, velocity);
		else if (Input::isKeyPressed(input::KEY_D))
			camera->move(Direction::RIGHT, velocity);
	}

	camera->update();
}

void CameraController::onResize(const std::shared_ptr<event::WindowResizedEvent>& evt)
{
	camera->onResize(evt->getWidth(), evt->getHeight());
}

void CameraController::processMouseMove(const std::shared_ptr<event::MouseMovedEvent>& evt)
{
	double xOffset = evt->getXPos() * mouseSensitivity;
	double yOffset = evt->getYPos() * mouseSensitivity;

	camera->setPitch((float)yOffset);
	camera->setYaw((float)xOffset);
}

void CameraController::processMouseScroll(const std::shared_ptr<event::MouseScrolledEvent>& evt)
{
	camera->doZoom((float)evt->getYOffset() * scrollSensitivity);
}
