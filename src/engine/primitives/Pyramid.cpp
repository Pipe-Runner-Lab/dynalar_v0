#include "Pyramid.h"

void Pyramid::InitializeUniforms()
{
}

Pyramid::Pyramid() :
	vertices{
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f
	},
	indices{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	},
	va(VertexArray()),
	vb(VertexBuffer(
		vertices,
		sizeof(vertices)
	)),
	layout(VertexBufferLayout()),
	ib(IndexBuffer(indices, sizeof(indices) / sizeof(GLuint))),
	shader(Shader("assets/shaders/pyramid.vert", "assets/shaders/pyramid.frag"))
{
	layout.Push<float>(3); // vertices

	va.AddBuffer(vb, layout);
}

void Pyramid::Draw(const Renderer& renderer)
{
	renderer.Draw(va, ib, shader);
}
