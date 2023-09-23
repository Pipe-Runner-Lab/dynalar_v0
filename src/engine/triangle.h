#pragma once

#include <glm/glm.hpp>

class Triangle {
private:
	GLuint m_VAO = 0, m_VBO = 0, m_program = 0;
	glm::mat4 m_model = glm::mat4(1.0f);
	GLfloat vertices[3 * 3] = {
		-1.0f, -1.0f, 0.0f, // Left
		1.0f, -1.0f, 0.0f, // Right
		0.0f, 1.0f, 0.0f // Top
	};

private:
	void applyTransform(glm::mat4 model);

public:
	Triangle();
	void move(float x, float y, float z);
	void draw();
};