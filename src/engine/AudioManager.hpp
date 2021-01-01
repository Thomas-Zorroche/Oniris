#pragma once
#include <unordered_map>
#include <irrklang/irrKlang.h>
#include <irrklang/irrKlang.h>
#include <glm/glm.hpp>

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

	void Play(const std::string& path, float volume = 1.0f);
	void Stop(const std::string& path);
	void SetListenerPosition(glm::vec3 position, glm::vec3 lookdir);
	void SetUpSea();
	void SetUpRiver();
	void PlayWind();


private:
	AudioManager() {};
	~AudioManager() {};
	//std::unordered_map<std::string, AudioPlayer> _Audios;
	irrklang::ISoundEngine* _Engine = irrklang::createIrrKlangDevice();
	void PlaySea(glm::vec3 position);
	void PlayWater(glm::vec3 position);
	void Play3D(const std::string& path, glm::vec3 position, float volume, float minDist = 0.0f );
};
