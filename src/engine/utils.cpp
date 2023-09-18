#include <iostream>
#include <GLEW/glew.h>
#include "utils.h"
#include <string.h>

GLuint CompileShader(char* srcCode, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	GLint codeLength = strlen(srcCode);

	glShaderSource(shader, 1, &srcCode, nullptr); // notice address of pointer
	glCompileShader(shader);

	// Check for errors
	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024] = { 0 };
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error compiling " << (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader") << std::endl;
		std::cout << infoLog << std::endl;
		exit(1);
	}

	return shader;
}

// TODO: Rename to create shader program
GLuint CompileShaders(char* vShaderSrc, char* fShaderSrc) {
	GLuint program = glCreateProgram();

	GLuint vetexShader = CompileShader(vShaderSrc, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fShaderSrc, GL_FRAGMENT_SHADER);

	glAttachShader(program, vetexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program); // send program to GPU

	// Check for errors
	GLint success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024] = { 0 };
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error linking program: " << infoLog << std::endl;
		exit(1);
	}

	// Validate program
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024] = { 0 };
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error validating program: " << infoLog << std::endl;
		exit(1);
	}

	// Delete intermediate shader outputs
	glDeleteShader(vetexShader);
	glDeleteShader(fragmentShader);

	return program;
}