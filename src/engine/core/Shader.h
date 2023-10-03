#pragma once

#include <string>
#include "GLEW/glew.h"
#include "glm/glm.hpp"

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

	void SetUniform1i(const std::string& name, int v0);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix);
private:
	GLuint CompileShader(const std::string& srcCode, GLenum shaderType);
	GLuint CreateShader(const std::string& vShaderSrc, const std::string& fShaderSrc);
	std::string ParseShader(const std::string& filename);
	GLint GetUnifromLocation(const std::string& name);
};

