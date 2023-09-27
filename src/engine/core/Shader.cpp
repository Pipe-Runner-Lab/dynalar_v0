#include "Shader.h"
#include <iostream>
#include "../utils.h"

GLuint Shader::CompileShader(char* srcCode, GLenum shaderType) {
	GLCall(GLuint shader = glCreateShader(shaderType));
	GLint codeLength = strlen(srcCode);

	GLCall(glShaderSource(shader, 1, &srcCode, nullptr)); // notice address of pointer
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

GLuint Shader::CreateShader(char* vShaderSrc, char* fShaderSrc) {
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

void Shader::ParseShader(const std::string& filename) {
	// TODO: Implement
}

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath): m_vertFilepath(vertexShaderFilePath), m_fragFilepath(fragmentShaderFilePath)
{
	char* vShaderSrc = (char*)R"(
		#version 330

		layout (location = 0) in vec3 pos;
	
		out vec3 vColor;

		void main() {
			vColor = clamp(pos, 0.0f, 1.0f);
			gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
		}
	)";

	// fragment shader
	char* fShaderSrc = (char*)R"(
		#version 330

		out vec4 colour; // only possible output from fragment shader, so name not important
		in vec3 vColor;

		void main() {
			colour = vec4(vColor, 1.0);
		}
	)";

	m_RendererID = CreateShader(vShaderSrc, fShaderSrc);
}

Shader::~Shader()
{
	
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
}

GLuint Shader::GetUnifromLocation(const std::string& name)
{
	return GLuint();
}
