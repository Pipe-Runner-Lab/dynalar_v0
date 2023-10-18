#pragma once

#include <glm/glm.hpp>

class AmbientLight
{
private:
	float m_intensity;
	glm::vec3 m_color;

public:
	AmbientLight();
	AmbientLight(float intensity, glm::vec3 color);

	inline float& GetIntensity() {
		return m_intensity;
	};

	inline glm::vec3& GetColor() {
		return m_color;
	};
};

