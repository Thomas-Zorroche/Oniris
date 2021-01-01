#pragma once
#include "gameplay/Object.hpp"
#include "hud/Hud.hpp"

class TransformLayout;


class NarrativeObject : public Object
{
public:
	NarrativeObject(const Model& model, const TransformLayout&, const std::string& panelName);
	~NarrativeObject();

	void OnOverlap() override;

private:
	//NarrativeObjectType _Type = TEXT;
	//bool IsText() { return (_Type == TEXT); }

	std::string _panelName;

};

