#pragma once

#include "../core/Texture.h"
#include "../core/IndexBuffer.h"
#include "../core/VertexArray.h"
#include "../core/VertexBuffer.h"
#include "../Renderer.h"
#include <GLEW/glew.h>

class TexturedSquare
{
private:
	Texture texture;
	GLfloat vertices[4 * 5];
	GLuint indices[6];
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;

private:
		void InitializeUniforms();
public:
	TexturedSquare();

	void Draw(const Renderer& renderer);
};

