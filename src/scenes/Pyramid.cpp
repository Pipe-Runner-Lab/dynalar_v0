#include "Pyramid.h"
#include <glm/gtc/type_ptr.hpp>

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
renderer(Renderer(camera, glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f))),
model(glm::mat4(1.0f)),
translation(glm::vec3(0.0f, 0.0f, -20.0f))
{
	layout.Push<float>(3); // vertices
	va.AddBuffer(vb, layout);
}

void scene::Pyramid::OnUpdate(float deltaTime, WindowManager& windowManager)
{
	model = glm::rotate(model, deltaTime * 0.005f, glm::vec3(0, 1, 0));
}

void scene::Pyramid::OnRender()
{
	shader.Bind();
	shader.SetUniformMatrix4f("u_model", glm::translate(model, translation));
	renderer.Draw(va, ib, shader);
}

void scene::Pyramid::OnImGUIRender()
{
	ImGui::SliderFloat3("Translation", glm::value_ptr(translation), -100.0f, 0.0f);
}
