#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "object.h"

class Pyramid : public Object {
private:
	GLuint m_VAO = 0, m_VBO = 0, m_IBO = 0, m_program = 0;
	glm::mat4 m_model = glm::mat4(1.0f);
	// TODO: Use bufferWidth and bufferHeight to calculate aspect ratio
	glm::mat4 m_projection = glm::perspective(45.0f, 800.0f / 600.0f,0.1f, 100.0f);
	GLuint indices[12] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};
	GLfloat vertices[3 * 4] = {
		-1.0f, -1.0f, 0.0f, // Left
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, // Right
		0.0f, 1.0f, 0.0f // Top
	};

public:
	Pyramid();
	void move(float x, float y, float z) override;
	void scale(float x, float y, float z) override;
	void rotateX(float angle) override;
	void rotateY(float angle) override;
	void rotateZ(float angle) override;

	// TODO: Find a way to create transformation pipeline
	void draw() override;
};