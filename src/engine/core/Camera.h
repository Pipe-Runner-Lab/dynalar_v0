#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	glm::mat4 m_ViewMatrix;

public:
	Camera();
	glm::mat4& GetViewMatrix();
};

