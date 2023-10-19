#include "DirectionalLight.h"

DirectionalLight::DirectionalLight():
	m_color(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_ambientIntensity(1.0f),
	m_diffuseIntensity(1.0f),
	m_direction(glm::vec3(0.0f, -1.0f, 0.0f))
{
}

DirectionalLight::DirectionalLight(float ambientIntensity, glm::vec3 color, float diffuseIntensity, glm::vec3 direction):
	m_color(color),
	m_ambientIntensity(ambientIntensity),
	m_diffuseIntensity(diffuseIntensity),
	m_direction(direction)
{
}


