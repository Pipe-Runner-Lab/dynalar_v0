#include "SpotLigh.h"

SpotLight::SpotLight() :
	m_color(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_ambientIntensity(1.0f),
	m_diffuseIntensity(1.0f),
	m_position(glm::vec3(0.0f, -1.0f, 0.0f)),
	m_direction(glm::vec3(0.0f, -1.0f, 0.0f)),
	m_attenuation(Attenuation{ 0.0f, 0.0f, 1.0f }),
	m_coneAngle(45.0f)
{
}

SpotLight::SpotLight(float ambientIntensity, glm::vec3 color, float diffuseIntensity, glm::vec3 position, glm::vec3 direction, Attenuation attenuation, float coneAngle) :
	m_color(color),
	m_ambientIntensity(ambientIntensity),
	m_diffuseIntensity(diffuseIntensity),
	m_position(position),
	m_attenuation(attenuation),
	m_direction(direction),
	m_coneAngle(coneAngle)
{
}


