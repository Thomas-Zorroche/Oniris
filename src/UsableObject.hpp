#pragma once
#include "Object.hpp"


enum UsableObjectType
{
	KEY,
	MAP
};

class UsableObject : public Object
{
public:
	UsableObject(const Model& model, const glm::vec3& position, const std::string& panelName);
	~UsableObject();

	void Use();

	void OnOverlap() override 
	{
		std::cout << "Usable Object\n";
	}

	
private:
	UsableObjectType _Type = KEY;
	bool _InInventory = false;

	bool IsInInventory() { return _InInventory; }

	std::string _panelName;
	
};

