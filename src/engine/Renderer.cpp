#include "Renderer.h"
#include "GLEW/glew.h"
#include "glm/glm.hpp"

Renderer::Renderer(Camera& camera) : 
	m_ProjectionMatrix(glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f)),
	camera(camera)
{
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const
{
	shader.Bind();

	shader.SetUniformMatrix4f("u_projection", m_ProjectionMatrix);
	shader.SetUniformMatrix4f("u_view", camera.m_ViewMatrix);
	
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);

	ib.Unbind();
	va.Unbind();
	shader.Unbind();
}

void Renderer::Clear() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // TODO: Look into how this works
}
