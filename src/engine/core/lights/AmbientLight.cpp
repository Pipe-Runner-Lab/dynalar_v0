#include "AmbientLight.h"

AmbientLight::AmbientLight():
	m_color(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_intensity(1.0f)
{
}

AmbientLight::AmbientLight(float intensity, glm::vec3 color):
	m_intensity(intensity),
	m_color(color)
{
}
