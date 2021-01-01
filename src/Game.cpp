#include "Game.hpp"
#include "Portal.hpp"

Game::Game()
	: _portal(std::make_shared<Portal>())
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




