#include "AudioManager.hpp"
#include <iostream>

void AudioManager::Play(const std::string& path, float volume) {
	if (!_Engine->isCurrentlyPlaying(path.c_str()))
	{
		irrklang::ISound* snd = _Engine->play2D(path.c_str(), true, false, true);
		snd->setVolume(volume);
		snd->drop();
	}

}


void AudioManager::Stop(const std::string& path) {
	if (_Engine->isCurrentlyPlaying(path.c_str()))
		_Engine->stopAllSoundsOfSoundSource(_Engine->getSoundSource(path.c_str()));
}

void AudioManager::PlayWind() {
	Play3D("res/audio/wind.mp3", glm::vec3(600.0f, 80.0f, 500.0f), 1.0f, 8.0f); 

	//
	// [ TODO ] : placer le vent au niveaux du portail (proche d'une falaise)
	//
}

void AudioManager::PlayForest() {
	Play3D("res/audio/forest.mp3", glm::vec3(450.0f, 15.0f, 250.0f), 1.0f, 12.0f);

	//
	// [ TODO ] : placer au centre de la for�t
	//

}


void AudioManager::Play3D(const std::string& path, glm::vec3 position, float volume, float minDist ) {
	irrklang::ISound* snd = _Engine->play3D(path.c_str(), irrklang::vec3df(position.x, position.y, position.z), true, false, true);
	if (!snd)
		return;
	snd->setVolume(volume);
	snd->setMinDistance(minDist);

	snd->drop();
}

void AudioManager::PlaySea(glm::vec3 position) {
	Play3D("res/audio/sea.mp3", position, 1.0f, 2.0f);

}

void AudioManager::PlayWater(glm::vec3 position) {
	Play3D("res/audio/river.mp3", position, 1.0f);
}

void AudioManager::SetListenerPosition(glm::vec3 position, glm::vec3 lookdir) {
	_Engine->setListenerPosition(irrklang::vec3df(position.x, position.y, position.z), irrklang::vec3df(lookdir.x, lookdir.y, lookdir.z));
}

void AudioManager::SetUpRiver() {
	PlayWater(glm::vec3(430.0f, 15.0f, 410.0f));
	PlayWater(glm::vec3(260.0f, 15.0f, 300.0f));
}

void AudioManager::SetUpSea() {
	PlaySea(glm::vec3(200.0f, 0.0f, 200.0f));
	PlaySea(glm::vec3(200.0f, 0.0f, 800.0f));
	PlaySea(glm::vec3(800.0f, 0.0f, 800.0f));
	PlaySea(glm::vec3(800.0f, 0.0f, 200.0f));
	PlaySea(glm::vec3(0.0f, 0.0f, 500.0f));
	PlaySea(glm::vec3(1000.0f, 0.0f, 500.0f));
	PlaySea(glm::vec3(500.0f, 0.0f, 1000.0f));
	PlaySea(glm::vec3(500.0f, 0.0f, 500.0f));
}