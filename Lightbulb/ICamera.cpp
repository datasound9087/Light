#include "lbpch.h"
#include "lightbulb/core/ICamera.h"

const float ICamera::DEFAULT_MOVEMENT_SPEED = 2.5f;
const float ICamera::DEFAULT_MOUSE_SENSITIVITY = 0.1f;
const float ICamera::DEFAULT_ZOOM_LEVEL_MIN = 1.0f;
const float ICamera::DEFAULT_ZOOM_LEVEL_MAX = 45.0f;
const float ICamera::DEFAULT_ZOOM_LEVEL = 1.0f;

void ICamera::update()
{
	updateCameraVectors();
	updateProjViewMatrix();
}

void ICamera::setZoom(float zoom)
{
	if (zoom < minZoom)
		this->zoom = minZoom;
	else if (zoom > maxZoom)
		this->zoom = maxZoom;
	else
		this->zoom = zoom;
}

void ICamera::updateProjViewMatrix()
{
	viewMatrix = glm::lookAt(position, position + direction, up);
	projViewMatrix = projMatrix * viewMatrix;
}

void ICamera::updateCameraVectors()
{
	glm::vec3 dir;
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(dir);

	right = glm::normalize(glm::cross(direction, worldUp));
	up = glm::normalize(glm::cross(right, direction));
}
