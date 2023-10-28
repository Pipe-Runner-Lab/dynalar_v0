#pragma once

#include "../utils.h"
#include "GLEW/glew.h"
#include <string>

class Texture
{
private:
	GLuint m_RendererID;
	std::string m_filePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP; // BPP => Bits Per Pixel 

public:
	Texture(const std::string& filePath, bool hasAlpha = true);
	~Texture();

	void Bind(GLuint slot = 0) const;
	void Unbind() const;

	inline int GetHeight() const { return m_Height; }
	inline int GetWidth() const { return m_Width; }
};

