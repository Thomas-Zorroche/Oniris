#pragma once

#include "Object.hpp"
#include <memory>

class StaticMesh;


class InteractiveObject : public Object
{
public:
	InteractiveObject(const Model& model, const glm::vec3& position, const std::string& panelName, 
		const std::shared_ptr<StaticMesh>& ioObject);

	~InteractiveObject();

	void OnOverlap() override;

	virtual void Interact() = 0;

protected:

	std::string _panelName;

	// Graphical representation of the object
	std::shared_ptr<StaticMesh> _ioObject;

};