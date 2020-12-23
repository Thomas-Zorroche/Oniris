#pragma once

#include "StaticMesh.hpp"

class Fog;

class Ocean
{
public:
	Ocean(const std::shared_ptr<Fog>& fog);

	void Draw();


private:
	StaticMesh _staticMesh;
};