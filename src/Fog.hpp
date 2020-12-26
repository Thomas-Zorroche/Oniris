#pragma once

#include "glm/glm.hpp"

/*
* SAVE
* SUN : 1.0, 0.9, 0.7
* SHADOW : 0.5, 0.6, 0.7
* SKY : 0.5, 0.6, 0.7
* 
*/

class Fog
{
public:
	Fog() = default;

	std::pair<glm::vec3, glm::vec3> Color() const { return { _colorShadow, _colorSun }; }
	glm::vec3 ColorSky() const { return _colorSky; }
	const float Density() const { return _density; }
	const float Gradient() const { return _gradient; }
	const float Height() const { return _height; }
	const float LowerLimit() const { return _lowerLimit; }
	const float UpperLimit() const { return _upperLimit; }

private:
	// Simple Fog
	glm::vec3 _colorShadow = glm::vec3(0.5, 0.6, 0.7);
	glm::vec3 _colorSun = glm::vec3(1.0, 0.9, 0.7);	
	float amountSun = 0.005f;									// Amount of fog coming from Sun (keep this value small)
	float gradientSunShadow = 1.0f;
	float be = 0.01f;											// exctinction
	float bi = 0.04f;											// inscattering

	// Deep Blue Fog											// Fog around the player
	glm::vec3 _deepFog = glm::vec3(0.0, 0.1, 0.25);
	float factorDeepFog = 0.5f;									// Intensity of the fog	(between 0 and 1)
	float distanceDeepFog = 0.02;							    // 1 : minimale distance / 0 : infinity

	// Sky Fog
	glm::vec3 _colorSky = glm::vec3(0.925, 0.709, 0.654);

	float _density = 0.01f;
	float _gradient = 0.5f;
	float _height = 30.0f;

	// Attenuation on Skybox
	float _lowerLimit = 35.0f;
	float _upperLimit = 80.0f;
};
