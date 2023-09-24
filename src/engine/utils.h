#include <GLEW/glew.h>

#pragma once

#define ASSERT(x) if (!(x)) __debugbreak(); // __debugbreak() is a Visual Studio specific function
# define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

GLuint CompileShaders(char* vShaderSrc, char* fShaderSrc);