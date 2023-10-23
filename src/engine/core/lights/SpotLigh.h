#pragma once

#include <glm/glm.hpp>
#include "PointLight.h"

class SpotLight
{
private:
	float m_ambientIntensity;
	glm::vec3 m_color;
	float m_diffuseIntensity;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	Attenuation m_attenuation;
	float m_coneAngle; // in degrees

public:
	SpotLight();
	SpotLight(float ambientIntensity, glm::vec3 color, float diffuseIntensity, glm::vec3 position, glm::vec3 direction, Attenuation attenuation, float coneAngle);

	inline float& GetAmbientIntensity() {
		return m_ambientIntensity;
	};

	inline float& GetDiffuseIntensity() {
		return m_diffuseIntensity;
	};

	inline glm::vec3& GetColor() {
		return m_color;
	};

	inline glm::vec3& GetPosition() {
		return m_position;
	};

	inline glm::vec3& GetDirection() {
		return m_direction;
	}

	inline Attenuation& GetAttenuation() {
		return m_attenuation;
	};

	inline float& GetRawConeAngle() {
		return m_coneAngle; // in degs
	};

	inline float GetConeAngle() {
		return cosf(glm::radians(m_coneAngle)); // normalize cone angle b/w [1,0]
	};
};

