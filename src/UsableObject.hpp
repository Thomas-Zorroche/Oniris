#pragma once
#include "Object.hpp"
#include "Hud.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"

class TransformLayout;

class UsableObject : public Object
{
public:
	UsableObject(const Model& model, const TransformLayout& transLayout, const std::string& panelName, 
		const std::string& type, const std::shared_ptr<Game>& game);
	~UsableObject();

	void OnOverlap() override;

	
private:
	std::string _Type = "key";
	std::string _panelName;
	std::shared_ptr<Game> _gamePtr;
	
};

