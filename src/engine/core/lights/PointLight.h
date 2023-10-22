#pragma once

#include <glm/glm.hpp>

struct Attenuation {
	float exponent_coef;
	float linear_coef;
	float constant_coef;
};

class PointLight
{
private:
	float m_ambientIntensity;
	glm::vec3 m_color;
	float m_diffuseIntensity;
	glm::vec3 m_position;
	Attenuation m_attenuation;

public:
	PointLight();
	PointLight(float ambientIntensity, glm::vec3 color, float diffuseIntensity, glm::vec3 position, Attenuation attenuation);

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

	inline Attenuation& GetAttenuation() {
		return m_attenuation;
	};
};

