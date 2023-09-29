#pragma once

#include "core/IndexBuffer.h"
#include "core/VertexArray.h"
#include "core/Shader.h"


class Renderer
{
public:
	void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const;
	void Clear() const;
};

