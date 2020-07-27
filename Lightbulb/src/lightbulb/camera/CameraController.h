#pragma once
#include "lightbulb\camera\ICamera.h"
#include "lightbulb/event/Event.h"
#include "lightbulb/event/KeyboardEvents.h"
#include "lightbulb/event/WindowEvents.h"
#include "lightbulb/event/MouseEvents.h"

class CameraController
{
public:
	static const float DEFAULT_MOVEMENT_SPEED;
	static const float DEFAULT_MOUSE_SENSITIVITY;
	static const float DEFAULT_SCROLL_SENSITIVITY;

public:
	CameraController(const std::shared_ptr<ICamera>& camera, bool canMove, bool canRotate, bool canZoom)
		: camera(camera), canMove(canMove), canRotate(canRotate), canZoom(canZoom)
	{}

	void onEvent(const std::shared_ptr<event::Event>& evt);
	void update();

	void onResize(const std::shared_ptr<event::WindowResizedEvent>& evt);

	void lock() { locked = true; }
	void unlock() { locked = false; }

	void enableZoom(bool enabled) { canZoom = enabled; }
	void enableMove(bool enabled) { canMove = enabled; }
	void enableRotate(bool enabled) { canRotate = enabled; }

	const std::shared_ptr<ICamera>& getCamera() const { return camera; }
	void setCamera(const std::shared_ptr<ICamera>& camera) { this->camera = camera; }

	const float getMovementSpeed() const { return movementSpeed; }
	void setMovementSpeed(float speed) { movementSpeed = speed; }

	const float getMouseSensitivity() const { return mouseSensitivity; }
	void setMouseSensitivity(float sensitivity) { mouseSensitivity = sensitivity; }

	const float getScrollSensitivity() const { return scrollSensitivity; }
	void setScrollSensitivity(float sensitivity) { scrollSensitivity = sensitivity; }

private:
	void processMouseMove(const std::shared_ptr<event::MouseMovedEvent>& evt);
	void processMouseScroll(const std::shared_ptr<event::MouseScrolledEvent>& evt);

private:
	bool locked = false;
	bool canZoom = false;
	bool canMove = true;
	bool canRotate = false;
	std::shared_ptr<ICamera> camera;

	float movementSpeed = DEFAULT_MOVEMENT_SPEED;
	float mouseSensitivity = DEFAULT_MOUSE_SENSITIVITY;
	float scrollSensitivity = DEFAULT_SCROLL_SENSITIVITY;
};

