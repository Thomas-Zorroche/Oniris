#include "UsableObject.hpp"
#include "ResourceManager.hpp"
#include "StaticMesh.hpp"

UsableObject::UsableObject(const Model& model, const TransformLayout& transLayout, const std::string& panelName, const std::string& type)
	: Object(model, transLayout), _panelName(panelName), _Type(type)
{

}


UsableObject::~UsableObject() {};


void UsableObject::OnOverlap() 
{

	if (_InWorld)
	{
		Hud::Get().SetState(ScreenState::OVERLAP_UO);
		Hud::Get().SetVisibility("p_pickup", true);
		Hud::Get().SetTarget(1);

	}

	if (InputHandler::Get().GetActiveKey() == ActiveKey::E)
	{
		if (_InWorld)
		{
			std::cout << "pick up\n";
			Game::Get().PickUp(_Type);
			Hud::Get().Translate(_Type);
			_InWorld = false;
		}
	}

}