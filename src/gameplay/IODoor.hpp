#pragma once

#include "gameplay/InteractiveObject.hpp"
#include "lighting/LightManager.hpp"

class StaticMesh;

class IODoor : public InteractiveObject
{
public:
	IODoor(const Model& model, const TransformLayout& transLayout, const std::string& panelName, const std::shared_ptr<StaticMesh>& ioObject)
		: InteractiveObject(model, transLayout, panelName, ioObject) {};
	

private:
	void Interact();
	bool _open = false;

};

void IODoor::Interact()
{

	if (_open)
	{
		std::cout << "Fermee" << std::endl;
		_open = false;
		_panelName = "p_open";
		_ioObject->Rotate(glm::vec3(0, -90, 0));
	}
	else
	{
		std::cout << "Ouverte" << std::endl;
		_open = true;
		_panelName = "p_close";
		_ioObject->Rotate(glm::vec3(0, 90, 0));
	}
}