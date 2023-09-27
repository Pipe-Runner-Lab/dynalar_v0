#pragma once

#include <GLEW/glew.h>
#include "../core/IndexBuffer.h"
#include "../core/VertexArray.h"
#include "../core/Shader.h"

class TriangleImp
{
private:
	GLfloat vertices[3 * 3] = {
		-1.0f, -1.0f, 0.0f, // Left
		1.0f, -1.0f, 0.0f, // Right
		0.0f, 1.0f, 0.0f // Top
	};
	GLuint indices[3] = {
		0, 1, 2
	};

	GLuint m_program = 0;
	VertexArray va = VertexArray();
	IndexBuffer ib = IndexBuffer(indices, sizeof(indices) / sizeof(GLuint));
	Shader shader = Shader("./something", "./something");

public:
	TriangleImp();

	// TODO: Find a way to create transformation pipeline
	void draw();
};

