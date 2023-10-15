#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	shader(Shader("assets/shaders/texture2D.vert", "assets/shaders/texture2D.frag")),
	camera(Camera()),
	renderer(Renderer(camera, glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f))),
	model_1(glm::mat4(1.0f)),
	model_2(glm::mat4(1.0f)),
	translation_1(glm::vec3(2.5f, 0.0f, 0.0f)),
	translation_2(glm::vec3(-2.5f, 0.0f, 0.0f))
{
	layout.Push<float>(3); // vertices
	layout.Push<float>(2); // texture coordinates

	va.AddBuffer(vb, layout);

	// Initialize Uniforms

	shader.Bind();
	shader.SetUniform1i("u_Texture", 0); // setting slot in shader
	shader.SetUniform4f("u_color", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.Unbind();
}

void scene::Texture2D::OnRender()
{
	texture.Bind(0); // activating slot

	shader.Bind();
	shader.SetUniformMatrix4f("u_model", glm::translate(model_1, translation_1));
	renderer.Draw(va, ib, shader);

	shader.Bind();
	shader.SetUniformMatrix4f("u_model", glm::translate(model_1, translation_2));
	renderer.Draw(va, ib, shader);
}

void scene::Texture2D::OnImGUIRender()
{
	ImGui::SliderFloat3("Translation A", glm::value_ptr(translation_1), -5.0f, 5.0f);
	ImGui::SliderFloat3("Translation B", glm::value_ptr(translation_2), -5.0f, 5.0f);
}
