#include "gameplay/UsableObject.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/StaticMesh.hpp"

UsableObject::UsableObject(const Model& model, const TransformLayout& transLayout, const std::string& panelName, 
	const std::string& type, const std::shared_ptr<Game>& game)
	: Object(model, transLayout), _panelName(panelName), _Type(type), _gamePtr(game)
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
			_gamePtr->PickUp(_Type);
			Hud::Get().Translate(_Type, _gamePtr);
			_InWorld = false;
		}
	}
}