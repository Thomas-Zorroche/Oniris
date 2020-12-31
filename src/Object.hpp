#pragma once
#include "Model.hpp"
#include <string>
#include "glm/glm.hpp"

class StaticMesh;
class TransformLayout;

//
// Object is an Interface 
//
class Object
{
public:
	Object(const Model& model, const TransformLayout& transLayout);
	virtual ~Object();

	void Draw();

	bool IsInWorld() const { return _InWorld; }

	virtual void OnOverlap() = 0;


protected:
	std::shared_ptr<StaticMesh> _staticMesh;
	bool _InWorld = true;
};

