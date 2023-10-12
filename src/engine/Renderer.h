#pragma once

#include "core/IndexBuffer.h"
#include "core/VertexArray.h"
#include "core/Shader.h"
#include "core/Camera.h"
#include <glm/gtc/matrix_transform.hpp>


class Renderer
{
private:
	glm::mat4 m_ProjectionMatrix;
	Camera camera;

public:
	Renderer(Camera& camera);
	Renderer(Camera& camera, glm::mat4 projectionMatrix);
	void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const;
	static void Clear();
};

