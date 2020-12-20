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
	UsableObject(const Model& model, const glm::vec3& position, const std::string& panelName, const CollisionLayout& cLayout);
	~UsableObject();

	void Use();

	static void FunctionTest() {
		std::cout << "HIT USABLE OBJ \n";
	}
	
private:
	UsableObjectType _Type = KEY;
	bool _InInventory = false;

	bool IsInInventory() { return _InInventory; }

	std::string _panelName;
	
};

