#include "TriangleImp.h"
#include "../utils.h"
#include "../core/VertexBufferLayout.h"
#include "../core/VertexBuffer.h"

TriangleImp::TriangleImp()
{
	char* vShaderSrc = (char*)R"(
		#version 330

		layout (location = 0) in vec3 pos;
	
		out vec3 vColor;

		void main() {
			vColor = clamp(pos, 0.0f, 1.0f);
			gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
		}
	)";

	// fragment shader
	char* fShaderSrc = (char*)R"(
		#version 330

		out vec4 colour; // only possible output from fragment shader, so name not important
		in vec3 vColor;

		void main() {
			colour = vec4(vColor, 1.0);
		}
	)";

	m_program = CompileShaders(vShaderSrc, fShaderSrc);

	//va = VertexArray();

	VertexBuffer vb = VertexBuffer(
		vertices,
		sizeof(vertices)
	);

	VertexBufferLayout layout = VertexBufferLayout();
	layout.Push<float>(3);

	va.AddBuffer(vb, layout);

	//ib = IndexBuffer(indices, sizeof(indices) / sizeof(GLuint));

}

void TriangleImp::draw()
{
	GLCall(glUseProgram(m_program));
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);

	ib.Unbind();
	va.Unbind();
	GLCall(glUseProgram(0));
}
