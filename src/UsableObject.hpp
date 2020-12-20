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
	UsableObject(const Model& model, glm::vec3 position, CollisionLayout cLayout);
	~UsableObject();

	void Use();

	static void FunctionTest() {
		std::cout << "HIT USABLE OBJ \n";
	}
	
private:
	UsableObjectType _Type = KEY;
	bool _InInventory = false;

	bool IsInInventory() { return _InInventory; }
	
};

