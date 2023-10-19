#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <GLEW/glew.h>
#include <STB/stb_image.h>
#include "utils.h"

void GLClearError(){
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

