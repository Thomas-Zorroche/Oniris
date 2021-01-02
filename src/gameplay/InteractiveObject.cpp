#include "gameplay/InteractiveObject.hpp"
#include "hud/Hud.hpp"
#include "engine/InputHandler.hpp"
#include "engine/StaticMesh.hpp"

InteractiveObject::InteractiveObject(const Model& model, const TransformLayout& transLayout, const std::string& panelName, 
	const std::shared_ptr<StaticMesh>& ioObject)
	: Object(model, transLayout, panelName), _ioObject(ioObject)
{
}

InteractiveObject::~InteractiveObject() {};

void InteractiveObject::OnOverlap()
{
	Hud::Get().SetVisibility(_panelName, true);
	Hud::Get().SetState(ScreenState::OVERLAP_IO);
	Hud::Get().SetTarget(1);

	if (InputHandler::Get().GetActiveKey() == ActiveKey::E 
	 && InputHandler::Get().CanInteract())
	{	
		Interact();
		InputHandler::Get().SetCanInteract(false);
	}

}