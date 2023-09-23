#include <GLEW/glew.h>
#include "utils.h"
#include "triangle.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Triangle::Triangle() {
	// vertex shader
	char* vShaderSrc = (char*)R"(
		#version 330

		layout (location = 0) in vec3 pos;
		uniform mat4 model;

		void main() {
			gl_Position = model * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
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
	glGenVertexArrays(1, &m_VAO);
	// Bind VAO
	glBindVertexArray(m_VAO);

	// Create VBO
	glGenBuffers(1, &m_VBO);
	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO); // notice GL_ARRAY_BUFFER (other options available too)

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
	m_program = CompileShaders(vShaderSrc, fShaderSrc);

	// apply default transform
	applyTransform(m_model);
}

void Triangle::applyTransform(glm::mat4 model) {
	glUseProgram(m_program);
	GLint modelLoc = glGetUniformLocation(m_program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUseProgram(0);
}

void Triangle::move(float x, float y, float z) {
	glm::mat4 model = glm::translate(m_model, glm::vec3(x, y, z));
	applyTransform(model);
}

void Triangle::draw() {
	glUseProgram(m_program);
	glBindVertexArray(m_VAO);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glBindVertexArray(0);
	glUseProgram(0);
}