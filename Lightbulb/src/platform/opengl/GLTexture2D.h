#pragma once
#include <glad/glad.h>
#include "lightbulb/renderer/resource/texture/Texture2D.h"

class GLTexture2D : public Texture2D
{
public:
	GLTexture2D(const std::string& name, const std::string& path, bool flipOnLoad, const TextureProps& props);
	GLTexture2D(const std::string& name, int width, int height, const TextureProps& props);
	virtual ~GLTexture2D();

	void bind(const uint32_t slot) override;
	void unBnd() override;

private:
	unsigned char* readFromFile(const std::string& path, bool flipOnLoad);
	void createTexture(unsigned char* data = nullptr);
	void setTextureFormatFromFile(int numChannels);

	GLenum getGLTextureWrapMode(const TextureWrapping::Type& wrapping);
	GLenum getGLTextureFilterMode(const TextureFiltering::Type& filter);
	GLenum getGLTextureFormatMode(const TextureFormat::Type& format);

private:
	GLuint id;
};

