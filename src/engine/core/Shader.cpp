#include "Shader.h"
#include <iostream>
#include <fstream>
#include "../utils.h"

GLuint Shader::CompileShader(const std::string& srcCode, GLenum shaderType) {
	GLCall(GLuint shader = glCreateShader(shaderType));
	GLint codeLength = srcCode.length();
	const char* c_srcCode = srcCode.c_str();

	GLCall(glShaderSource(shader, 1, &c_srcCode, nullptr)); // notice address of pointer
	GLCall(glCompileShader(shader));

	// Check for errors
	GLint success = 0;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success) {
		GLchar infoLog[1024] = { 0 };
		GLCall(glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog));
		std::cout << "Error compiling " << (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader") << std::endl;
		std::cout << infoLog << std::endl;
		exit(1);
	}

	return shader;
}

GLuint Shader::CreateShader(const std::string& vShaderSrc, const std::string& fShaderSrc) {
	GLCall(GLuint program = glCreateProgram());

	GLuint vetexShader = CompileShader(vShaderSrc, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fShaderSrc, GL_FRAGMENT_SHADER);

	GLCall(glAttachShader(program, vetexShader));
	GLCall(glAttachShader(program, fragmentShader));

	GLCall(glLinkProgram(program)); // send program to GPU

	// Check for errors
	GLint success = 0;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
	if (!success) {
		GLchar infoLog[1024] = { 0 };
		GLCall(glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog));
		std::cout << "Error linking program: " << infoLog << std::endl;
		exit(1);
	}

	// Validate program
	GLCall(glValidateProgram(program));
	GLCall(glGetProgramiv(program, GL_VALIDATE_STATUS, &success));
	if (!success) {
		GLchar infoLog[1024] = { 0 };
		GLCall(glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog));
		std::cout << "Error validating program: " << infoLog << std::endl;
		exit(1);
	}

	// Delete intermediate shader outputs
	GLCall(glDeleteShader(vetexShader));
	GLCall(glDeleteShader(fragmentShader));

	return program;
}

std::string Shader::ParseShader(const std::string& filename) {
	std::string content = "";
	std::ifstream fileStream = std::ifstream(filename.c_str(), std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return "";
	}

	std::string line = "";

	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();

	return content;
}

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath): m_vertFilepath(vertexShaderFilePath), m_fragFilepath(fragmentShaderFilePath)
{
	const std::string vShaderSrc = ParseShader(vertexShaderFilePath);
	const std::string fShaderSrc = ParseShader(fragmentShaderFilePath);

	m_RendererID = CreateShader(vShaderSrc, fShaderSrc);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind()
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind()
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUnifromLocation(name), v0, v1, v2, v3));
}

GLint Shader::GetUnifromLocation(const std::string& name)
{
	GLCall(GLint location = glGetUniformLocation(m_RendererID, name.c_str()));

	if (location == -1) {
		std::cout << "Warning: " << name << " does not exist" << std::endl;
	}

	return location;
}
