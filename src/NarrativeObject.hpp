#pragma once
#include "Object.hpp"
#include "Hud.hpp"

enum NarrativeObjectType
{
	TEXT,
	MODEL,
	SOUND
};

class NarrativeObject : public Object
{
public:
	NarrativeObject(const Model& model, const glm::vec3& position, const std::string& panelName);
	~NarrativeObject();

	void Read();

	void OnOverlap() override
	{	

		if (Hud::Get().GetState() != ScreenState::OBJMENU)
		Hud::Get().SetVisibility("observe", true);
		
		if (Hud::Get().GetState() == ScreenState::OBJMENU)
			Hud::Get().SetVisibility(_panelName, true);
		else
			Hud::Get().SetVisibility(_panelName, false);
		
		//Hud::Get().SetState(ScreenState::ONOVERLAP);

	}

private:
	NarrativeObjectType _Type = TEXT;

	bool IsText() { return (_Type == TEXT); }

	std::string _panelName;

};

