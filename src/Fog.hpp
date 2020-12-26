#pragma once

#include "glm/glm.hpp"

class Fog
{
public:
	Fog(const glm::vec3& colorShadow = glm::vec3(0.5, 0.6, 0.7),
		const glm::vec3& colorSun = glm::vec3(1.0, 0.9, 0.7),
		const glm::vec3& colorSky = glm::vec3(0.5, 0.6, 0.7),
		float density = 0.01f, float gradient = 0.5f, float height = 30.0f,
		float lowerLimit = 35.0f, float upperLimit = 80.0f)
		: _colorShadow(colorShadow), _colorSun(colorSun), _colorSky(colorSky), _density(density), _gradient(gradient), _height(height), _lowerLimit(lowerLimit), _upperLimit(upperLimit) {}

	std::pair<glm::vec3, glm::vec3> Color() const { return { _colorShadow, _colorSun }; }
	glm::vec3 ColorSky() const { return _colorSky; }
	const float Density() const { return _density; }
	const float Gradient() const { return _gradient; }
	const float Height() const { return _height; }
	const float LowerLimit() const { return _lowerLimit; }
	const float UpperLimit() const { return _upperLimit; }
private:
	glm::vec3 _colorShadow;
	glm::vec3 _colorSun;
	glm::vec3 _colorSky;
	float _density;
	float _gradient;
	float _height;

	float _lowerLimit;
	float _upperLimit;
};
