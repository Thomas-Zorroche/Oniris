#pragma once

#include "InteractiveObject.hpp"
#include "LightManager.hpp"

class StaticMesh;

class IODoor : public InteractiveObject
{
public:
	IODoor(const Model& model, const glm::vec3& position, const std::string& panelName, const std::shared_ptr<StaticMesh>& ioObject)
		: InteractiveObject(model, position, panelName, ioObject) {};
	

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
		_ioObject->Rotate(glm::vec3(0, -270, 0));
	}
	else
	{
		std::cout << "Ouverte" << std::endl;
		_open = true;
		_panelName = "p_lightoff";
		_ioObject->Rotate(glm::vec3(0, 270, 0));
	}
}