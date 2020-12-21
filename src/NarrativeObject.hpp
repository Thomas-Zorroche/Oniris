#pragma once
#include "Object.hpp"
#include "Hud.hpp"
#include "InputHandler.hpp"

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
		// A d�caler dans Object
		if (InputHandler::Get().GetState() == ScreenState::OBJMENU)
			Hud::Get().SetVisibility(_panelName, true);
		else
			Hud::Get().SetVisibility(_panelName, false);

		Hud::Get().SetVisibility("use", true);
	}

private:
	NarrativeObjectType _Type = TEXT;

	bool IsText() { return (_Type == TEXT); }

	std::string _panelName;

};

