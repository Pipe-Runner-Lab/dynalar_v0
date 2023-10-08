#include "Texture2D.h"

scene::Texture2D::Texture2D() :
	texture(Texture("assets/images/awesomeface.png")),
	vertices{
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // LB
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // RB
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // RT
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f, // LT
	},
	indices{
		0, 1, 2,
		2, 3, 0
	},
	va(VertexArray()),
	vb(VertexBuffer(
		vertices,
		sizeof(vertices)
	)),
	layout(VertexBufferLayout()),
	ib(IndexBuffer(indices, sizeof(indices) / sizeof(GLuint))),
	shader(Shader("assets/shaders/sample.vert", "assets/shaders/sample.frag")),
	camera(Camera()),
	renderer(Renderer(camera))
{
	layout.Push<float>(3); // vertices
	layout.Push<float>(2); // texture coordinates

	va.AddBuffer(vb, layout);

	//InitializeUniforms

	shader.Bind();
	shader.SetUniform1i("u_Texture", 0); // setting slot
	shader.SetUniform4f("u_color", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.Unbind();
}

void scene::Texture2D::OnRender()
{
	texture.Bind(0); // setting slot
	renderer.Draw(va, ib, shader);
}
