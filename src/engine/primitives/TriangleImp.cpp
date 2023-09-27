#include "TriangleImp.h"
#include "../utils.h"
#include "../core/VertexBufferLayout.h"
#include "../core/VertexBuffer.h"
#include "../core/Shader.h"

TriangleImp::TriangleImp()
{
	VertexBuffer vb = VertexBuffer(
		vertices,
		sizeof(vertices)
	);

	VertexBufferLayout layout = VertexBufferLayout();
	layout.Push<float>(3);

	va.AddBuffer(vb, layout);
}

void TriangleImp::draw()
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);

	ib.Unbind();
	va.Unbind();
	shader.Unbind();
}
