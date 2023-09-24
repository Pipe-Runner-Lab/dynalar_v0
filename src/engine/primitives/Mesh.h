#pragma once

#include <GLEW/glew.h>

class Mesh
{
private:
	GLuint m_VAO = 0, m_VBO = 0, m_IBO = 0, m_program = 0;
	GLuint indexCount, vertexCount;

public:
	Mesh(GLfloat* vertices, GLuint* indices);
	~Mesh();
	void render();

private:
	void create();
	void clear();
};

