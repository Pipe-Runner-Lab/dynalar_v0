#include "PointLight.h"

PointLight::PointLight() :
	m_color(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_ambientIntensity(1.0f),
	m_diffuseIntensity(1.0f),
	m_position(glm::vec3(0.0f, -1.0f, 0.0f)),
	m_attenuation(Attenuation{ 0.0f, 0.0f, 1.0f })
{
}

PointLight::PointLight(float ambientIntensity, glm::vec3 color, float diffuseIntensity, glm::vec3 position, Attenuation attenuation) :
	m_color(color),
	m_ambientIntensity(ambientIntensity),
	m_diffuseIntensity(diffuseIntensity),
	m_position(position),
	m_attenuation(attenuation)
{
}


