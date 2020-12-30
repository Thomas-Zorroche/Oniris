#include "InteractiveObject.hpp"
#include "Hud.hpp"
#include "InputHandler.hpp"
#include "StaticMesh.hpp"

InteractiveObject::InteractiveObject(const Model& model, const glm::vec3& position, const std::string& panelName, const std::shared_ptr<StaticMesh>& ioObject)
	: Object(model, position), _panelName(panelName), _ioObject(ioObject)
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