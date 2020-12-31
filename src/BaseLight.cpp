#include "BaseLight.hpp"

BaseLight::BaseLight(LightType type, float intensity, const glm::vec3& color)
	: _type(type), _intensity(intensity), _color(color) 
{
	_ambient = color;
	_diffuse = color;
	_specular = color;
}


// Getters & Setters
float BaseLight::Intensity() const
{
	return _intensity;
}
const glm::vec3& BaseLight::Ambient() const
{
	return _ambient; 
}
void BaseLight::SetAmbient(const glm::vec3& ambient)
{
	_ambient = ambient;
}

const glm::vec3& BaseLight::Diffuse() const
{
	return _diffuse;
}
void BaseLight::SetDiffuse(const glm::vec3& diffuse)
{
	_diffuse = diffuse;
}

const glm::vec3& BaseLight::Specular() const
{
	return _specular;
}
void BaseLight::SetSpecular(const glm::vec3& specular)
{
	_specular = specular;
}