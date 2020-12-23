#pragma once

#include "InteractiveObject.hpp"

class IOLight : public InteractiveObject
{
public:
	IOLight(const Model& model, const glm::vec3& position, const std::string& panelName) 
		: InteractiveObject(model, position, panelName){};
	~IOLight();

private:
	void Interact();
	bool _lightOn = false;

};


IOLight::~IOLight()
{
}

void IOLight::Interact() {

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