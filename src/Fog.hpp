#pragma once

#include "glm/glm.hpp"

class Fog
{
public:
	Fog(const glm::vec3& color = glm::vec3(0.32f, 0.78f, 0.76f), float density = 0.0085f, float gradient = 1.0f)
		: _color(color), _density(density), _gradient(gradient) {}

	const glm::vec3 Color() const { return _color; }
	const float Density() const { return _density; }
	const float Gradient() const { return _gradient; }
private:
	glm::vec3 _color;
	float _density;
	float _gradient;
};