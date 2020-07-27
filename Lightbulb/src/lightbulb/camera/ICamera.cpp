#include "lbpch.h"
#include "lightbulb/camera/ICamera.h"

const float ICamera::DEFAULT_ZOOM_LEVEL_MIN = 1.0f;
const float ICamera::DEFAULT_ZOOM_LEVEL_MAX = 45.0f;
const float ICamera::DEFAULT_ZOOM_LEVEL = 1.0f;

void ICamera::update()
{
	updateCameraVectors();
	updateProjViewMatrix();
}

void ICamera::move(const Direction& direction, float amount)
{
	switch (direction)
	{
	case Direction::LEFT:
		position -= right * amount;
		break;
	case Direction::RIGHT:
		position += right * amount;
		break;
	case Direction::UP:
		position -= up * amount;
		break;
	case Direction::DOWN:
		position += up * amount;
		break;
	}
}

void ICamera::setPitch(float pitch)
{
	this->pitch = pitch;

	if (constrainPitch)
		glm::clamp(pitch, -90.0f, 90.0f);
}

void ICamera::setZoom(float zoom)
{
	this->zoom = zoom;
	glm::clamp(this->zoom, minZoom, maxZoom);
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
