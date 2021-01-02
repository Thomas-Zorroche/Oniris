#pragma once

#include "glm/glm.hpp"
#include <utility>


class Fog
{
public:
	Fog() = default;

	std::pair<glm::vec3, glm::vec3> Color() const;
	glm::vec3 ColorSky() const;
	const float Density() const;
	const float Gradient() const;
	const float Height() const;
	const float LowerLimit() const;
	const float UpperLimit() const;

	void InsideDarkWorld(bool darkWorld);

private:
	// Simple Fog
	glm::vec3 _colorShadow = glm::vec3(0.25, 0.725, 0.825);
	glm::vec3 _colorSun = glm::vec3(0.800, 0.715, 0.600);
	float amountSun = 0.005f;									// Amount of fog coming from Sun (keep this value small)
	float gradientSunShadow = 1.0f;
	float be = 0.01f;											// exctinction
	float bi = 0.04f;											// inscattering

	// Deep Blue Fog											// Fog around the player
	glm::vec3 _deepFog = glm::vec3(0.0, 0.1, 0.25);
	float factorDeepFog = 0.5f;									// Intensity of the fog	(between 0 and 1)
	float distanceDeepFog = 0.02;							    // 1 : minimale distance / 0 : infinity

	// Sky Fog
	glm::vec3 _colorSky = glm::vec3(1.0, 0.85, 0.5);

	float _density = 0.01f;
	float _gradient = 0.5f;
	float _height = 30.0f;

	// Attenuation on Skybox
	float _lowerLimit = 35.0f;
	float _upperLimit = 80.0f;

	// =======================================================
	// Dark World
	// =======================================================
	bool _darkWorld = false;

	// Sky Fog
	glm::vec3 _colorSkyDW = glm::vec3(0.7, 0.6, 0.95);
};
