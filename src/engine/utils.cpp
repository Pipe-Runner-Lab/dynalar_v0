#include <iostream>
#include <GLEW/glew.h>
#include "utils.h"
#include <string.h>

void AddShader(GLuint program, char* srcCode, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	GLint codeLength = strlen(srcCode);

	glShaderSource(shader, 1, &srcCode, &codeLength); // notice address of pointer
	glCompileShader(shader);

	GLint success = 0;
	GLchar infoLog[1024] = { 0 };

	// Check for errors
	glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error compiling " << shader << " program: " << infoLog << std::endl;
		exit(1);
	}
}

GLuint CompileShaders(char* vShaderSrc, char* fShaderSrc) {
	std::cout << "Compiling shaders" << std::endl;

	GLuint shaderProgram = glCreateProgram();

	AddShader(shaderProgram, vShaderSrc, GL_VERTEX_SHADER);
	AddShader(shaderProgram, fShaderSrc, GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar infoLog[1024] = { 0 };

	glLinkProgram(shaderProgram); // send program to GPU

	// Check for errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error linking program: " << infoLog << std::endl;
		exit(1);
	}

	// Validate program
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error validating program: " << infoLog << std::endl;
		exit(1);
	}

	return shaderProgram;
}