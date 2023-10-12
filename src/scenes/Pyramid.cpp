#include "Pyramid.h"

scene::Pyramid::Pyramid() :
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
	shader(Shader("assets/shaders/pyramid.vert", "assets/shaders/pyramid.frag")),
	camera(Camera()),
	renderer(Renderer(camera, glm::perspective(45.0f, 16.0f/9.0f, -1.0f, 1.0f))),
	model_1(glm::mat4(1.0f)),
	translation_1(glm::vec3(2.5f, 0.0f, 0.0f))
{
	layout.Push<float>(3); // vertices
	va.AddBuffer(vb, layout);
}

void scene::Pyramid::OnUpdate(float deltaTime, WindowManager& windowManager)
{
}

void scene::Pyramid::OnRender()
{
	shader.Bind();
	renderer.Draw(va, ib, shader);
}

void scene::Pyramid::OnImGUIRender()
{
}
