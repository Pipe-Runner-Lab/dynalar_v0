#include "IndexBuffer.h"
#include "../utils.h"

IndexBuffer::IndexBuffer(const GLuint* data, GLuint count) : m_RendererID(0), m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendererID));
	
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
	Unbind();
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}