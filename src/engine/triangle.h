#pragma once

class Triangle {
private:
	GLuint VAO = 0, VBO = 0, shaderProgram = 0;
	GLfloat vertices[3 * 3] = {
		-1.0f, -1.0f, 0.0f, // Left
		1.0f, -1.0f, 0.0f, // Right
		0.0f, 1.0f, 0.0f // Top
	};

public:
	Triangle();
	void draw();
};