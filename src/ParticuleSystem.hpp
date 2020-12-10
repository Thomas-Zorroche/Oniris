#pragma once

#include "SpecialMesh.hpp"
#include "glm/glm.hpp"
#include "Texture.h"
#include "Terrain.hpp"
#include <memory>



class ParticuleSystem
{
public:
	ParticuleSystem(const StaticMesh& mesh, unsigned int count, const std::string& pathDensity, std::shared_ptr<Terrain>& terrain);

	void Draw();

private:
	StaticMesh _instance;
	unsigned int _instanceVAO;
	unsigned int _count;

	float _size = 1.0f;
	float _randomSize = 0.0f;

	float _randomRotationAmount = 0.0f;
	glm::vec3 _randomRotationAxis = glm::vec3(0.0, 1.0, 0.0);

	Texture _densityTexture;

	std::shared_ptr<Terrain> _terrain;
};