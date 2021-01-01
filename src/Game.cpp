#include "Game.hpp"

Game::Game()
	: _portal(std::make_shared<Portal>(Model("res/models/PortalPlan.obj"),
		TransformLayout(glm::vec3(499, 75, 578), glm::vec3(0, 0, 0), 2.2f)))
{

}

void Game::PickUp(const std::string& type)
{
	if (type == "key")
	{
		_HasKey = true;
	}

	else if (type == "map")
	{
		_HasMap = true;
	}

	else if (type == "crystal")
	{
		_crystalCount++;
		if (_crystalCount == 4)
		{
			_portal->Open();
		}
	}
}

void Game::PassThroughGate()
{
	if (_darkWorld)
		_darkWorld = false;
	else
		_darkWorld = true;
}


