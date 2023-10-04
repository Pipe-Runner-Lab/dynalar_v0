#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera():
	m_ViewMatrix(
		glm::translate(
			glm::mat4(1.0f), 
			glm::vec3(0.0f, 0.0f, 0.0f)
		)
	)
{
}

// TODO: Need to implement negation for camera transforms
glm::mat4& Camera::GetViewMatrix()
{
	// TODO: insert return statement here
	return m_ViewMatrix;
}
