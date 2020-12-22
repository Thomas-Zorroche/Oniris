#pragma once
#include "Model.hpp"
#include <string>
#include "glm/glm.hpp"

class StaticMesh;

//
// Object is an Interface (pure virtual fonction) 
//
class Object
{
public:
	Object(const Model& model, const glm::vec3& position);
	virtual ~Object();

	void Draw();
	bool IsInWorld() const { return _InWorld; }

	virtual void OnOverlap() = 0;
	//virtual void Use() = 0;

protected:
	std::shared_ptr<StaticMesh> _staticMesh;
	bool _InWorld = true;

	//bool _OnBeginOverlap = false;
};

