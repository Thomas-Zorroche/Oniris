#include "gameplay/Game.hpp"
#include "gameplay/Portal.hpp"
#include "engine/AudioManager.hpp"


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
		AudioManager::Get().Play("res/audio/pickup.wav", 0.5, false);
	}

	else if (type == "map")
	{
		_HasMap = true;
		AudioManager::Get().Play("res/audio/pickup.wav", 0.5, false);
	}

	else if (type == "crystal")
	{
		_crystalCount++;
		if (_crystalCount == 4)
		{
			_portal->Open();
		}
		AudioManager::Get().Play("res/audio/crystal.wav", 0.2, false);
	}
}




