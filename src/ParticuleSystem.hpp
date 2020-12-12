#pragma once

#include "SpecialMesh.hpp"
#include "glm/glm.hpp"
#include "Texture.h"
#include "Terrain.hpp"
#include <memory>
#include <string>


class ControlPointParticule
{
public:
	ControlPointParticule(const glm::vec2& position, int density = 1, float radius = 25.0f)
		: _position(position), _instanceCount(density), _radius(radius) {}

	//void DistanceBetweenCP(const ControlPointParticule& cp);
	glm::vec2 Position() const { return _position; }
	float Radius() const { return _radius; }

private:
	glm::vec2 _position;
	float _instanceCount;
	float _radius;
};


class ParticuleSystem
{
public:
	ParticuleSystem(const std::string& name, const StaticMesh& mesh, unsigned int count, 
		const std::vector<ControlPointParticule>& controlPoints, std::shared_ptr<Terrain>& terrain);

	void Draw();

private:
	std::string _name;

	StaticMesh _instance;
	unsigned int _instanceVAO;
	unsigned int _count;

	float _size = 1.0f;
	float _randomSize = 0.0f;

	float _randomRotationAmount = 0.0f;
	glm::vec3 _randomRotationAxis = glm::vec3(0.0, 1.0, 0.0);

	std::shared_ptr<Terrain> _terrain;
	std::vector<ControlPointParticule> _controlPoints;
};