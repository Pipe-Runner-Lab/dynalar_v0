#include "TexturePyramid.h"

#include <glm/gtc/type_ptr.hpp>

scene::TexturePyramid::TexturePyramid() :
	texture1(Texture("assets/images/brick.png")),
	texture2(Texture("assets/images/dirt.png")),
	vertices{
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,
		1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f
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
	shader(Shader("assets/shaders/texturedPyramid.vert", "assets/shaders/texturedPyramid.frag")),
	camera(Camera()),
	renderer(Renderer(camera, glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f))),
	model(glm::mat4(1.0f)),
	translation(glm::vec3(0.0f, 0.0f, -20.0f))
{
	layout.Push<float>(3); // vertices
	layout.Push<float>(2); // uv
	va.AddBuffer(vb, layout);

	// Initialize Uniforms

	shader.Bind();
	shader.SetUniform1i("u_Texture", 0); // setting slot in shader
	shader.Unbind();
}

void scene::TexturePyramid::OnUpdate(float deltaTime, WindowManager& windowManager)
{
	camera.Update(deltaTime, windowManager);
	//model = glm::rotate(model, deltaTime * 0.005f, glm::vec3(0, 1, 0));
}

void scene::TexturePyramid::OnRender()
{
	texture1.Bind(0); // activating slot

	shader.Bind();
	shader.SetUniformMatrix4f("u_model", glm::translate(model, translation));
	renderer.Draw(va, ib, shader);

	texture2.Bind(0); // activating slot

	shader.Bind();
	shader.SetUniformMatrix4f("u_model", glm::translate(model, translation + glm::vec3(0.0f, 5.0f, 0.0f)));
	renderer.Draw(va, ib, shader);
}

void scene::TexturePyramid::OnImGUIRender()
{
	ImGui::SliderFloat3("Translation", glm::value_ptr(translation), -100.0f, 0.0f);
}
