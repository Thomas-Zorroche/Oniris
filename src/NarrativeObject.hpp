#pragma once
#include "Object.hpp"
#include "Hud.hpp"

//enum NarrativeObjectType
//{
//	TEXT,
//	MODEL,
//	SOUND
//};

class NarrativeObject : public Object
{
public:
	NarrativeObject(const Model& model, const glm::vec3& position, const std::string& panelName);
	~NarrativeObject();

	void OnOverlap() override;

private:
	//NarrativeObjectType _Type = TEXT;
	//bool IsText() { return (_Type == TEXT); }

	std::string _panelName;

};

