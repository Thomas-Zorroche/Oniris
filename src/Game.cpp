#include "Game.hpp"
#include "Portal.hpp"
#include "AudioManager.hpp"

Game::Game()
	: _portal(std::make_shared<Portal>())
{

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




