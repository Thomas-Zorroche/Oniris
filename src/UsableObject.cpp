#include "UsableObject.hpp"
#include "ResourceManager.hpp"

UsableObject::UsableObject(const Model& model, const glm::vec3& position, const std::string& panelName, const std::string& type)
	: Object(model, position), _panelName(panelName), _Type(type)
{

}


UsableObject::~UsableObject() {};

void UsableObject::Use() {
	if (_Type == "key")
		std::cout << "key\n";
	else if (_Type == "map")
		std::cout << "map\n";
}

void UsableObject::OnOverlap() 
{
	if (_InWorld)
	{
		Hud::Get().SetState(ScreenState::OVERLAP_UO);
		Hud::Get().SetVisibility("p_pickup", true);
	}

	if (InputHandler::Get().GetActiveKey() == ActiveKey::E)
	{
		if (_InWorld)
		{
			std::cout << "pick up\n";
			Game::Get().PickUp(_Type);
			_InWorld = false;
		}
	}
	
}