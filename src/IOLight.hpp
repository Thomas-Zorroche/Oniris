#pragma once

#include "InteractiveObject.hpp"
#include "LightManager.hpp"

class StaticMesh;

class IOLight : public InteractiveObject
{
public:
	IOLight(const Model& model, const TransformLayout& transLayout, const std::string& panelName, const std::shared_ptr<StaticMesh>& ioObject) 
		: InteractiveObject(model, transLayout, panelName, ioObject){};
	

private:
	void Interact();
	bool _lightOn = false;

};


void IOLight::Interact() 
{
	LightManager::Get().SwitchLights();

	if (_lightOn)
	{
		std::cout << "Eteins" << std::endl;
		_lightOn = false;
		_panelName = "p_lightup";
	}
	else
	{
		std::cout << "Allume" << std::endl;
		_lightOn = true;
		_panelName = "p_lightoff";
	}
}