#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lightbulb/util/Direction.h"

class ICamera
{
public:
	static const float DEFAULT_ZOOM_LEVEL;
	static const float DEFAULT_ZOOM_LEVEL_MIN;
	static const float DEFAULT_ZOOM_LEVEL_MAX;

public:
	ICamera(const glm::mat4& projMatrix)
		: projMatrix(projMatrix), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), up(worldUp)
	{
		update();
	}

	ICamera(const glm::mat4& projMatrix, const glm::vec3& position)
		: projMatrix(projMatrix), position(position), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), up(worldUp)
	{
		update();
	}

	virtual ~ICamera() = default;
	void update();

	const glm::mat4& getViewProjMatrix() const { return projViewMatrix; }
	const glm::mat4& getViewMatrix() const { return viewMatrix; };
	const glm::mat4& getProjMatrix() const { return projMatrix; }

	const glm::vec3& getPosition() const { return position; }
	void setPosition(const glm::vec3& pos) { position = pos; }
	
	void move(const Direction& direction, float amount);
	void moveX(float amount) { position.x += amount; }
	void moveY(float amount) { position.y += amount; }
	void moveZ(float amount) { position.z += amount; }
	void move(const glm::vec3& amount) { position += amount; }

	const glm::vec3& getDirection() const { return direction; }
	void setDirection(const glm::vec3& direction) { this->direction = direction; }

	float getYaw() const { return yaw; }
	void setYaw(float yaw) { this->yaw = yaw; }

	float getPitch() const { return pitch; }
	void setPitch(float pitch);

	void shouldContrainPitch(bool should) { constrainPitch = should; }

	float getMinZoom() const { return minZoom; }
	void setMinZoom(float minZoom) { this->minZoom = minZoom; }
	float getMaxZoom() const { return maxZoom; }
	void setMaxZoom(float pitch) { this->maxZoom = maxZoom; }

	float getZoom() { return zoom; }
	virtual void setZoom(float zoom);
	void resetZoom() { setZoom(DEFAULT_ZOOM_LEVEL); }

protected:
	void updateProjViewMatrix();
	void updateCameraVectors();

protected:
	glm::mat4 projViewMatrix;
	glm::mat4 projMatrix;
	glm::mat4 viewMatrix = glm::mat4(1.0f);

	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	glm::vec3 direction = {0.0f, 0.0f, -1.0f};
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool constrainPitch = true;

	float minZoom = DEFAULT_ZOOM_LEVEL_MIN;
	float maxZoom = DEFAULT_ZOOM_LEVEL_MAX;
	float zoom = DEFAULT_ZOOM_LEVEL;

	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
};
