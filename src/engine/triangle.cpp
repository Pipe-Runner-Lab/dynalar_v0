#include <GLEW/glew.h>
#include "utils.h"
#include "triangle.h"
#include <iostream>

Triangle::Triangle() {
	// vertex shader
	char* vShaderSrc = (char*)R"(
		#version 330

		layout (location = 0) in vec3 pos;

		void main() {
			gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
		}
	)";

	// fragment shader
	char* fShaderSrc = (char*)R"(
		#version 330

		out vec4 colour; // only possible output from fragment shader, so name not important

		void main() {
			colour = vec4(1.0, 0.0, 0.0, 1.0);
		}
	)";

	// Create VAO
	glGenVertexArrays(1, &VAO);
	// Bind VAO
	glBindVertexArray(VAO);

	// Create VBO
	glGenBuffers(1, &VBO);
	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // notice GL_ARRAY_BUFFER (other options available too)

	// Copy vertices to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // other options is GL_DYNAMIC draw

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // 0 is the index of the attribute
	glEnableVertexAttribArray(0); // enable vertex attribute array

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Create and compile shaders
	shaderProgram = CompileShaders(vShaderSrc, fShaderSrc);
}

void Triangle::draw() {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glBindVertexArray(0);
	glUseProgram(0);
}