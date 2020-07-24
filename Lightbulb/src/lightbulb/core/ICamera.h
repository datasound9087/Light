#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class ICamera
{
public:
	ICamera(const glm::mat4& projMatrix)
		: projMatrix(projMatrix), viewMatrix(1.0f)
	{
		updateProjViewMatrix();
	}

	virtual ~ICamera() = default;
	const glm::mat4& getViewProjMatrix() const { return projViewMatrix; }
	const glm::mat4& getViewMatrix() const { return viewMatrix; };
	const glm::mat4& getProjMatrix() const { return projMatrix; }

	const glm::vec3& getPosition() const { return position; }
	void setPosition(const glm::vec3& pos) { position = pos; }

protected:
	glm::mat4 projViewMatrix;
	glm::mat4 projMatrix;
	glm::mat4 viewMatrix;

	glm::vec3 position = { 0.0f, 0.0f, 0.0f };

	void updateProjViewMatrix()
	{
		projViewMatrix = projMatrix * viewMatrix;
	}
};
