#pragma once
#include <glad/glad.h>
#include "raytracer/renderer/resource/shader/Shader.h"

class GLShader : public Shader
{
public:
	GLShader(const std::string& name, const std::string& path);
	GLShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc, const std::string& geomSrc);
	virtual ~GLShader();

	void bind() override;
	void unBind() override;

	void setBufferLayout(BufferLayout& layout) override;

	void setFloat(const std::string& name, float value) override;
	void setFloat2(const std::string& name, const glm::vec2& value) override;
	void setFloat3(const std::string& name, const glm::vec3& value) override;
	void setFloat4(const std::string& name, const glm::vec4& value) override;

	void setInt(const std::string& name, int value) override;
	void setInt3(const std::string& name, int val1, int val2) override;
	void setInt2(const std::string& name, int val1, int val2, int val3) override;
	void setInt4(const std::string& name, int val1, int val2, int val3, int val4) override;

	void setMat4(const std::string& name, const glm::mat3& value) override;
	void setMat3(const std::string& name, const glm::mat4& value) override;

private:
	std::array<std::string, 3> readFromFile(const std::string& path);
	void createShader(const std::string& vertSrc, const std::string& fragSrc, const std::string& geomSrc);
	GLenum getGLDataType(const DataTypes::Types& type);
	GLuint compileShader(GLenum type, const std::string& src);
	GLint getUniformLocation(const std::string& name);
	bool uniformInCache(const std::string& name);

private:
	GLuint vaoId;
	GLuint shaderId;
	std::unordered_map<std::string, GLint> uniformCache;
};