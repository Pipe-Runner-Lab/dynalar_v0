#include "VertexBufferLayout.h"

unsigned int VertexBufferElement::GetSize(GLuint type)
{
	switch (type) {
	case(GL_FLOAT):				return 4;
	case(GL_UNSIGNED_INT):		return 4;
	case(GL_UNSIGNED_BYTE):		return 1;
	}

	ASSERT(false);
	return 0;
}

VertexBufferLayout::VertexBufferLayout() : m_stride(0) {}

//inline const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
//{
//	return m_VertexBufferElements;
//}

//inline GLuint VertexBufferLayout::GetStride() const {
//	return m_stride;
//}
