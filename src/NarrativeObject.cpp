#include "NarrativeObject.hpp"

NarrativeObject::NarrativeObject(const Model& model, const glm::vec3& position, const std::string& panelName)
	: Object(model, position), _panelName(panelName)
{

}

NarrativeObject::~NarrativeObject() {};


void NarrativeObject::OnOverlap() 
{
	if (Hud::Get().GetState() != ScreenState::OBJMENU)
	{
		Hud::Get().SetState(ScreenState::OVERLAP_NO);
		Hud::Get().SetVisibility(_panelName, false);
		Hud::Get().SetVisibility("p_observe", true);
		Hud::Get().SetTarget(1);

	}
	else
	{

		Hud::Get().SetVisibility(_panelName, true);
	}
}