#include "NarrativeObject.hpp"

NarrativeObject::NarrativeObject(const Model& model, const glm::vec3& position, const std::string& panelName)
	: Object(model, position), _panelName(panelName)
{

}

NarrativeObject::~NarrativeObject() {};


void NarrativeObject::OnOverlap() {
	{

		if (Hud::Get().GetState() != ScreenState::OBJMENU)
			Hud::Get().SetVisibility("p_observe", true);

		if (Hud::Get().GetState() == ScreenState::OBJMENU)
			Hud::Get().SetVisibility(_panelName, true);
		else
			Hud::Get().SetVisibility(_panelName, false);

		//Hud::Get().SetState(ScreenState::ONOVERLAP);

	}
}