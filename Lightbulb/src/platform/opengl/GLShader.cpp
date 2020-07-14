#include "lbpch.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include "GLShader.h"

GLShader::GLShader(const std::string& name, const std::string& path)
{
	this->name = name;
	std::array<std::string, 3> srcs = readFromFile(path);
	createShader(srcs[0], srcs[1], srcs[2]);
}

GLShader::GLShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc, const std::string& geomSrc)
{
	this->name = name;
	createShader(vertSrc, fragSrc, geomSrc);
}

GLShader::GLShader(const std::string& name, const std::string& src, bool dummy)
{
	this->name = name;
	std::array<std::string, 3> srcs = parseSrc(src);
	createShader(srcs[0], srcs[1], srcs[2]);
}

GLShader::~GLShader()
{
	glDeleteProgram(shaderId);
	glDeleteVertexArrays(1, &vaoId);
}

void GLShader::bind()
{
	glBindVertexArray(vaoId);
	glUseProgram(shaderId);
}

void GLShader::unBind()
{
	glUseProgram(0);
	glBindVertexArray(0);
}

std::array<std::string, 3> GLShader::readFromFile(const std::string& path)
{
	std::string result;
	std::ifstream in(path, std::ios::in | std::ios::binary);

	if (in)
	{
		//go to end of file
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();

		if (size != -1)
		{
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
			in.close();
		}
		else
			ERROR("Could not read shader file: {0}", path);
	}
	else
		ERROR("Could not read shader file: {0}", path);

	return parseSrc(result);
}

std::array<std::string, 3> GLShader::parseSrc(const std::string& src)
{
	//seperate parts of file
	const int READING_VERT = 0;
	const int READING_FRAG = 1;
	const int READING_GEOM = 2;
	const std::string SHADER_TYPE_FLAG = "#type";
	const std::string SHADER_TYPE_VERT = "vertex";
	const std::string SHADER_TYPE_FRAG = "fragment";
	const std::string SHADER_TYPE_GEOM = "geometry";
	std::stringstream ss(src);
	std::array<std::stringstream, 3> srcs;

	int readingType = -1;
	std::string line;
	while (std::getline(ss, line))
	{
		if (line.find(SHADER_TYPE_FLAG, 0) == 0)
		{
			if (line.find(SHADER_TYPE_VERT) != std::string::npos)
			{
				readingType = READING_VERT;
				continue;
			}
			else if (line.find(SHADER_TYPE_FRAG) != std::string::npos)
			{
				readingType = READING_FRAG;
				continue;
			}
			else if (line.find(SHADER_TYPE_GEOM) != std::string::npos)
			{
				readingType = READING_GEOM;
				continue;
			}
			else
			{
				ERROR("invalid GL shader type: {0}", line);
			}
		}
		else
		{
			srcs[readingType] << line << "\n";
		}
	}

	return {srcs[0].str(), srcs[1].str(), srcs[2].str()};
}

void GLShader::createShader(const std::string& vertSrc, const std::string& fragSrc, const std::string& geomSrc)
{
	GLuint program = glCreateProgram();
	bool addGeomShader = geomSrc != "";

	GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertSrc);
	GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragSrc);
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	GLuint geomShader = 0;
	if (addGeomShader)
	{
		geomShader = compileShader(GL_GEOMETRY_SHADER, geomSrc);
		glAttachShader(program, geomShader);
	}

	glLinkProgram(program);

	GLint linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint errorlogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorlogLength);

		std::vector<GLchar> infoLog(errorlogLength);
		glGetProgramInfoLog(program, errorlogLength, &errorlogLength, &infoLog[0]);
	
		glDeleteProgram(program);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		if(addGeomShader) glDeleteShader(geomShader);

		ERROR("Shader link Error:\n    {0}", infoLog.data());
		ASSERT(false, "Shader link failure");
	}

	glDetachShader(program, vertShader);
	glDeleteShader(vertShader);
	glDetachShader(program, fragShader);
	glDeleteShader(fragShader);
	if (addGeomShader)
	{
		glDetachShader(program, geomShader);
		glDeleteShader(geomShader);
	}

	shaderId = program;
}

GLenum GLShader::getGLDataType(const DataTypes::Types& type)
{
	switch (type)
	{
	case DataTypes::Types::Byte: return GL_BYTE;
	case DataTypes::Types::uByte: return GL_UNSIGNED_BYTE;
	case DataTypes::Types::Float: return GL_FLOAT;
	case DataTypes::Types::Float2: return GL_FLOAT;
	case DataTypes::Types::Float3: return GL_FLOAT;
	case DataTypes::Types::Float4: return GL_FLOAT;
	case DataTypes::Types::uInt: return GL_UNSIGNED_INT;
	}

	ERROR("Invalid vertex attrib type {0}", type);
}

GLuint GLShader::compileShader(GLenum type, const std::string& src)
{
	GLuint shader = glCreateShader(type);

	const char* charSrc = src.c_str();
	glShaderSource(shader, 1, &charSrc, NULL);
	glCompileShader(shader);

	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint errorLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLogLength);

		std::vector<GLchar> infoLog(errorLogLength);
		glGetShaderInfoLog(shader, errorLogLength, &errorLogLength, &infoLog[0]);
		glDeleteShader(shader);

		ERROR("Shader Compile {1} Error:\n    {0}", infoLog.data(), type == GL_VERTEX_SHADER ? "Vertex" : type == GL_FRAGMENT_SHADER ? "Fragment" : "Geometry");
		ASSERT(false, "Shader compile failure");
	}

	return shader;
}

void GLShader::setLayout(BufferLayout& layout)
{
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	GLuint locationIndex = 0;
	for (auto& element : layout.getElements())
	{
		glVertexAttribPointer(locationIndex, element.numPerVertex, getGLDataType(element.type), element.normalised, layout.getStride(), (void*)element.offset);
		glEnableVertexAttribArray(locationIndex);
		locationIndex++;
	}
}

GLint GLShader::getUniformLocation(const std::string& name)
{
	if (uniformInCache(name))
		return uniformCache[name];
	else
	{
		GLint location = glGetUniformLocation(shaderId, name.c_str());
		uniformCache[name] = location;
		return location;
	}
}

bool GLShader::uniformInCache(const std::string& name)
{
	return uniformCache.count(name) > 0;
}

void GLShader::setFloat(const std::string& name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void GLShader::setFloat2(const std::string& name, const glm::vec2& value)
{
	glUniform2f(getUniformLocation(name), value.x, value.y);
}

void GLShader::setFloat3(const std::string& name, const glm::vec3& value)
{
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void GLShader::setFloat4(const std::string& name, const glm::vec4& value)
{
	glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void GLShader::setInt(const std::string& name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void GLShader::setInt3(const std::string& name, int val1, int val2)
{
	glUniform2i(getUniformLocation(name), val1, val2);
}

void GLShader::setInt2(const std::string& name, int val1, int val2, int val3)
{
	glUniform3i(getUniformLocation(name), val1, val2, val3);
}

void GLShader::setInt4(const std::string& name, int val1, int val2, int val3, int val4)
{
	glUniform4i(getUniformLocation(name), val1, val2, val3, val4);
}

void GLShader::setIntArray(const std::string& name, int* arr, uint32_t count)
{
	glUniform1iv(getUniformLocation(name), count, arr);
}

void GLShader::setMat4(const std::string& name, const glm::mat3& value)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void GLShader::setMat3(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
