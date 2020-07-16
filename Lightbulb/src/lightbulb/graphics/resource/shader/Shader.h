#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include "lightbulb/graphics/resource/IGPUResource.h"
#include "lightbulb/graphics/resource/buffer/BufferLayout.h"

class Shader : public IGPUResource
{
public:
	static std::shared_ptr<Shader> create(const std::string& name, const std::string& path);
	static std::shared_ptr<Shader> create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc, const std::string& geometrySrc = "");
	static std::shared_ptr<Shader> create(const std::string& name, const std::string& src, bool dummy);

	virtual void setLayout(BufferLayout& layout) = 0;

	virtual void setFloat(const std::string& name, float value) = 0;
	virtual void setFloat2(const std::string& name, const glm::vec2& value) = 0;
	virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
	virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;

	virtual void setInt(const std::string& name, int value) = 0;
	virtual void setInt3(const std::string& name, int val1, int val2) = 0;
	virtual void setInt2(const std::string& name, int val1, int val2, int val3) = 0;
	virtual void setInt4(const std::string& name, int val1, int val2, int val3, int val4) = 0;

	virtual void setIntArray(const std::string& name, int* arr, uint32_t count) = 0;

	virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;
	virtual void setMat3(const std::string& name, const glm::mat3& value) = 0;

	const std::string& getName() const { return name; }

protected:
	std::string name;
};

