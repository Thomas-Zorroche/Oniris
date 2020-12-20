#include "UsableObject.hpp"
#include "ResourceManager.hpp"

UsableObject::UsableObject(const Model& model, const glm::vec3& position, const std::string& panelName, const CollisionLayout& cLayout)
	: Object(model, position, cLayout), _panelName(panelName)
{

}


UsableObject::~UsableObject() {};

void UsableObject::Use() {
	if (_Type == KEY)
		std::cout << "key\n";
	else if (_Type == MAP)
		std::cout << "map\n";
}
