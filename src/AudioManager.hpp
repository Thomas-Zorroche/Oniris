#pragma once
#include <unordered_map>
#include <irrklang/irrKlang.h>
#include <irrklang/ik_ISoundEngine.h>

class AudioManager
{
public:
	static AudioManager& Get()
	{
		static AudioManager instance;
		return instance;
	}

	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	//void Init() {
	//	AudioPlayer music = AudioPlayer("musicbox.mp3");
	//	AudioPlayer foot = AudioPlayer("footsteps.wav");
	//	_Audios.insert({ "music", music });
	//	_Audios.insert({ "footstep", foot });
	//}

	//void Play(const std::string& name) {
	//	_Audios.find(name)->second.Play();
	// }

	void Play(const std::string& path) {
		if(!_Engine->isCurrentlyPlaying(path.c_str()))
			_Engine->play2D(path.c_str(), true);
	}

	void Stop(const std::string& path) {
		if (_Engine->isCurrentlyPlaying(path.c_str()))
			_Engine->stopAllSoundsOfSoundSource(_Engine->getSoundSource(path.c_str()));
	}

private:
	AudioManager() {};
	~AudioManager() {};
	//std::unordered_map<std::string, AudioPlayer> _Audios;
	irrklang::ISoundEngine* _Engine = irrklang::createIrrKlangDevice();
};
