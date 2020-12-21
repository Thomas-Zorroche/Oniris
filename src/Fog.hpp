#pragma once

#include "glm/glm.hpp"

class Fog
{
public:
	Fog(const glm::vec3& color = glm::vec3(0.32f, 0.78f, 0.76f), float density = 0.01f, float gradient = 0.5f, float height = 30.0f,
		float lowerLimit = 35.0f, float upperLimit = 80.0f)
		: _color(color), _density(density), _gradient(gradient), _height(height), _lowerLimit(lowerLimit), _upperLimit(upperLimit) {}

	const glm::vec3 Color() const { return _color; }
	const float Density() const { return _density; }
	const float Gradient() const { return _gradient; }
	const float Height() const { return _height; }
	const float LowerLimit() const { return _lowerLimit; }
	const float UpperLimit() const { return _upperLimit; }
private:
	glm::vec3 _color;
	float _density;
	float _gradient;
	float _height;

	float _lowerLimit;
	float _upperLimit;
};