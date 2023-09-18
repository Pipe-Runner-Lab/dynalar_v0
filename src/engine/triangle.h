#pragma once

class Triangle {
private:
	GLuint m_VAO = 0, m_VBO = 0, m_program = 0;
	GLfloat vertices[3 * 3] = {
		-1.0f, -1.0f, 0.0f, // Left
		1.0f, -1.0f, 0.0f, // Right
		0.0f, 1.0f, 0.0f // Top
	};

public:
	Triangle();
	void draw();
};