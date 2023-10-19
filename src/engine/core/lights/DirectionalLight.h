#pragma once

#include <glm/glm.hpp>

class DirectionalLight
{
private:
	float m_ambientIntensity;
	glm::vec3 m_color;
	float m_diffuseIntensity;
	glm::vec3 m_direction;

public:
	DirectionalLight();
	DirectionalLight(float ambientIntensity, glm::vec3 color, float diffuseIntensity, glm::vec3 direction);

	inline float& GetAmbientIntensity() {
		return m_ambientIntensity;
	};

	inline float& GetDiffuseIntensity() {
		return m_diffuseIntensity;
	};

	inline glm::vec3& GetColor() {
		return m_color;
	};

	inline glm::vec3& GetDirection() {
		return m_direction;
	};
};

