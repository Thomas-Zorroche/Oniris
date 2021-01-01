#pragma once

#include "engine/StaticMesh.hpp"

class Fog;

class Ocean
{
public:
	Ocean(const std::shared_ptr<Fog>& fog);

	void Draw(const std::shared_ptr<Fog>& fog);


private:
	StaticMesh _staticMesh;
};