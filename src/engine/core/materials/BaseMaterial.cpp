#include "BaseMaterial.h"

BaseMaterial::BaseMaterial():
	m_shininess(32),
	m_specularIntensity(1.0f)
{
}

BaseMaterial::BaseMaterial(float specularIntensity, float shininess) :
	m_shininess(shininess),
	m_specularIntensity(specularIntensity)
{

}
