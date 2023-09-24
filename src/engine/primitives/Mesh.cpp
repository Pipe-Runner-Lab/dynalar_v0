#include "Mesh.h"
#include "../utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(GLfloat* vertices, GLuint* indices) {
	vertexCount = sizeof(vertices) / sizeof(vertices[0]);
	indexCount = sizeof(indices) / sizeof(indices[0]);

	create();
}

Mesh::~Mesh() {
	clear();
}

void Mesh::create() {
	// vertex shader
	char* vShaderSrc = (char*)R"(
		#version 330

		layout (location = 0) in vec3 pos;
	
		out vec3 vColor;

		uniform mat4 model;
		uniform mat4 projection;

		void main() {
			vColor = clamp(pos, 0.0f, 1.0f);
			gl_Position = projection * model * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
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

	// Create IBO
	glGenBuffers(1, &m_IBO);
	// Bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	// Copy indices to IBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // 0 is the index of the attribute
	glEnableVertexAttribArray(0); // enable vertex attribute array

	// Unbind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Create and compile shaders
	m_program = CompileShaders(vShaderSrc, fShaderSrc);
}

void Mesh::clear() {
	glDeleteBuffers(1, &m_IBO);
	m_IBO = 0;
	glDeleteBuffers(1, &m_VBO);
	m_VBO = 0;
	glDeleteVertexArrays(1, &m_VAO);
	m_VAO = 0;
	glDeleteProgram(m_program);
	m_program = 0;
}

void Mesh::render() {
	glUseProgram(m_program);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	GLint modelLoc = glGetUniformLocation(m_program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
	// TODO: Can be moved out of draw function
	GLint projectionLoc = glGetUniformLocation(m_program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}