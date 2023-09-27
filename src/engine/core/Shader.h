#pragma once

#include <string>
#include "GLEW/glew.h"

class Shader
{
private:
	GLuint m_RendererID = 0;
	std::string m_vertFilepath;
	std::string m_fragFilepath;

public:
	Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	~Shader();

	void Bind();
	void Unbind();

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	GLuint CompileShader(const std::string& srcCode, GLenum shaderType);
	GLuint CreateShader(const std::string& vShaderSrc, const std::string& fShaderSrc);
	std::string ParseShader(const std::string& filename);
	GLuint GetUnifromLocation(const std::string& name);
};

