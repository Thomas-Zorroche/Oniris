#include "InteractiveObject.hpp"
#include "Hud.hpp"
#include "InputHandler.hpp"

InteractiveObject::InteractiveObject(const Model& model, const glm::vec3& position, const std::string& panelName)
	: Object(model, position), _panelName(panelName)
{

}

InteractiveObject::~InteractiveObject() {};

void InteractiveObject::OnOverlap()
{
	Hud::Get().SetVisibility(_panelName, true);

	if (InputHandler::Get().GetActiveKey() == ActiveKey::E)
	{	
		Interact();
	}
}