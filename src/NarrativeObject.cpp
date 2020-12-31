#include "NarrativeObject.hpp"
#include "InputHandler.hpp"
#include "StaticMesh.hpp"

NarrativeObject::NarrativeObject(const Model& model, const TransformLayout& transLayout, const std::string& panelName)
	: Object(model, transLayout), _panelName(panelName)
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
		Hud::Get().SetVisibility(_panelName, true);

}