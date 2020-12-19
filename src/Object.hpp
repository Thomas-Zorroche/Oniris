#pragma once
#include "Mesh.hpp"
#include "SpecialMesh.hpp"
#include "Terrain.hpp"


class Object
{
public:
	Object(const std::string& path, const std::shared_ptr<Terrain>& terrain);
	virtual ~Object();

	virtual void Draw();
	//virtual void Use();

protected:
	std::shared_ptr<StaticMesh> _Mesh;
};

