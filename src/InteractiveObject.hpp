#pragma once

#include "Object.hpp"


class InteractiveObject : public Object
{
public:
	InteractiveObject(const Model& model, const glm::vec3& position, const std::string& panelName);
	~InteractiveObject();

	void OnOverlap() override;
	virtual void Interact() = 0 ;

protected:

	std::string _panelName;

};