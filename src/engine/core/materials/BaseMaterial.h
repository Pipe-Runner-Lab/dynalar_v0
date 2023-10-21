#pragma once

class BaseMaterial
{
private:
	float m_specularIntensity;
	float m_shininess;

public:
	BaseMaterial();
	BaseMaterial(float specularIntensity, float shininess);

	inline float& GetShininess() { return m_shininess; };
	inline float& GetSpecularIntensity() { return m_specularIntensity; };
};

