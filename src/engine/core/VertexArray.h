#pragma once

#include "./VertexBuffer.h"
#include "./VertexBufferLayout.h"

class VertexArray
{
private:
	GLuint m_RendererID = 0;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

