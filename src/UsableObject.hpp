#pragma once
#include "Object.hpp"
#include "Hud.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"



class UsableObject : public Object
{
public:
	UsableObject(const Model& model, const glm::vec3& position, const std::string& panelName, const std::string& type);
	~UsableObject();

	void Use();

	void OnOverlap() override
	{
		if (_InWorld)
		{
			Hud::Get().SetVisibility("use", true);
		}
		if (InputHandler::Get().GetActiveKey() == ActiveKey::E)
		{
			if (_InWorld)
			{
				std::cout << "pick up\n";
				Game::Get().PickUp(_Type);
				_InWorld = false;
			}
		}
		


	}

	
private:
	std::string _Type = "key";
	std::string _panelName;
	
};

