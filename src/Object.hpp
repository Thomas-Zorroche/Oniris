#pragma once
#include "StaticMesh.hpp"
#include "Terrain.hpp"

//
// Object is an Interface (pure virtual fonction) 
//
class Object
{
public:
	Object(const Model& model, const glm::vec3& position, const CollisionLayout& cLayout);
	virtual ~Object();

	void Draw();
	//virtual void Use() = 0;

protected:
	std::shared_ptr<StaticMesh> _Mesh;
};

