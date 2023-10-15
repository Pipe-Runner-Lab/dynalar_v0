#include "Texture.h"
#include <iostream>
#include <STB/stb_image.h>

Texture::Texture(const std::string& filePath): m_RendererID(0), m_filePath(filePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	GLCall(glGenTextures(1, &m_RendererID));
	//Bind(0, false);
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID))

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // setting minification filter to linear (image larger)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // setting magnification filter to linear (image smaller)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // s -> horizontal
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // t -> vertical

	// read data and store it in local buffer
	stbi_set_flip_vertically_on_load(true);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4); // desired channel 4 since RGBA
	if (m_LocalBuffer)
	{
		// sending texture data to GPU
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

		// generating mipmap
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	
	Unbind();

	// if localBuffer holds data, we free it here
	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(GLuint slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot)); // since GL_TEXTURE<number> are consecutive we can add directly
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID)); // other types of textures also exist
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
