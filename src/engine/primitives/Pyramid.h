#pragma once

#include "../core/IndexBuffer.h"
#include "../core/VertexArray.h"
#include "../core/VertexBuffer.h"
#include "../Renderer.h"
#include <GLEW/glew.h>

class Pyramid
{
private:
	GLfloat vertices[4 * 3];
	GLuint indices[12];
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;

private:
	void InitializeUniforms();
public:
	Pyramid();

	void Draw(const Renderer& renderer);
};

