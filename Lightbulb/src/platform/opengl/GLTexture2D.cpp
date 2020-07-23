#include "lbpch.h"
#include "GLTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glm/gtc/type_ptr.hpp>

GLTexture2D::GLTexture2D(const std::string& name, const std::string& path, bool flipOnLoad, const TextureProps& props)
{
	this->name = name;
	this->props = props;

	unsigned char* data = readFromFile(path, flipOnLoad);
	createTexture(data, true);
}

GLTexture2D::GLTexture2D(const std::string& name, int width, int height, const TextureProps& props)
{
	this->name = name;
	this->props = props;
	this->width = width;
	this->height = height;

	createTexture();
}

GLTexture2D::GLTexture2D(const std::string& name, int width, int height, unsigned char* data, const TextureProps& props)
{
	this->name = name;
	this->props = props;
	this->width = width;
	this->height = height;

	createTexture(data);
}

GLTexture2D::~GLTexture2D()
{
	glDeleteTextures(1, &id);
}

void GLTexture2D::bind(const uint32_t slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void GLTexture2D::unBnd()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned char* GLTexture2D::readFromFile(const std::string& path, bool flipOnLoad)
{
	stbi_set_flip_vertically_on_load(flipOnLoad);

	int width, height, numChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

	if (!data)
	{
		ERROR("Failed to load image: {0}", path);
		return nullptr;
	}

	this->width = width;
	this->height = height;
	setTextureFormatFromFile(numChannels);

	return data;
}

void GLTexture2D::createTexture(unsigned char* data, bool free)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getGLTextureWrapMode(props.wrapping.type));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getGLTextureWrapMode(props.wrapping.type));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getGLTextureFilterMode(props.filtering.minFilter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getGLTextureFilterMode(props.filtering.maxFilter));

	if (props.wrapping.type == TextureWrapping::Type::ClampBorder)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(props.wrapping.borderCol));

	if (props.format.format == TextureFormat::Type::RED)
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (props.mask.type == TextureMasking::Type::SwizzleRedAlpha)
	{
		GLint swizzleMask[] = { GL_ONE, GL_ONE, GL_ONE, GL_RED };
		glTexParameterIiv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, getGLTextureFormatMode(props.format.internalFormat), width, height, 0,
		getGLTextureFormatMode(props.format.format), GL_UNSIGNED_BYTE, data);

	if (props.genMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);

	if (free)
		stbi_image_free(data);
}

void GLTexture2D::setTextureFormatFromFile(int numChannels)
{
	if (numChannels == 1)
		props.format.setFormat(TextureFormat::Type::RED);
	else if(numChannels == 2)
		props.format.setFormat(TextureFormat::Type::RG);
	else if(numChannels == 3)
		props.format.setFormat(TextureFormat::Type::RGB);
	else
		props.format.setFormat(TextureFormat::Type::RGBA);
}

GLenum GLTexture2D::getGLTextureWrapMode(const TextureWrapping::Type& wrapping)
{
	switch (wrapping)
	{
	case TextureWrapping::Type::Repeat: return GL_REPEAT;
	case TextureWrapping::Type::MirroredRepeat: return GL_MIRRORED_REPEAT;
	case TextureWrapping::Type::ClampEdge: return GL_CLAMP_TO_EDGE;
	case TextureWrapping::Type::ClampBorder: return GL_CLAMP_TO_BORDER;
	}

	ERROR("Invalid texture wrapping type {0}", wrapping);
}

GLenum GLTexture2D::getGLTextureFilterMode(const TextureFiltering::Type& filter)
{
	switch (filter)
	{
	case TextureFiltering::Type::Nearest: return GL_NEAREST;
	case TextureFiltering::Type::Linear: return GL_LINEAR;
	case TextureFiltering::Type::MipmapNearestToNearest: return GL_NEAREST_MIPMAP_NEAREST;
	case TextureFiltering::Type::MipmapLinearToNearest: return GL_LINEAR_MIPMAP_NEAREST;
	case TextureFiltering::Type::MipmapNearestToLinear: return GL_NEAREST_MIPMAP_LINEAR;
	case TextureFiltering::Type::MipmapLinearToLinear: return GL_LINEAR_MIPMAP_LINEAR;
	}

	ERROR("Invalid texture filtering type {0}", filter);
}

GLenum GLTexture2D::getGLTextureFormatMode(const TextureFormat::Type& format)
{
	switch (format)
	{
	case TextureFormat::Type::RGB: return GL_RGB;
	case TextureFormat::Type::RGBA: return GL_RGBA;
	case TextureFormat::Type::RED: return GL_RED;
	case TextureFormat::Type::RG: return GL_RG;
	}

	ERROR("Invalid texture filtering type {0}", format);
}
