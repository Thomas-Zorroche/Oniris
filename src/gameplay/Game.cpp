#include "gameplay/Game.hpp"
#include "gameplay/Portal.hpp"

Game::Game()
	: _portal(std::make_shared<Portal>()) {}

std::shared_ptr<Portal> Game::PortalPtr() 
{ 
	return _portal; 
}

void Game::SetFog(const std::shared_ptr<Fog>& fog) 
{ 
	_portal->SetFog(fog); 
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




