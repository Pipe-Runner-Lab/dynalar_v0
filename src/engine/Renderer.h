#pragma once

#include "core/IndexBuffer.h"
#include "core/VertexArray.h"
#include "core/Shader.h"
#include <glm/gtc/matrix_transform.hpp>


class Renderer
{
private:
	glm::mat4 m_ProjectionMatrix;

public:
	Renderer();
	void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const;
	void Clear() const;
};

