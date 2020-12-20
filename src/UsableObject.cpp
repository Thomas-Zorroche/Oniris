#include "UsableObject.hpp"
#include "ResourceManager.hpp"

UsableObject::UsableObject(const Model& model, glm::vec3 position, CollisionLayout cLayout)
	: Object(model, position, cLayout)
{

}


UsableObject::~UsableObject() {};

void UsableObject::Use() {
	if (_Type == KEY)
		std::cout << "key\n";
	else if (_Type == MAP)
		std::cout << "map\n";
}
