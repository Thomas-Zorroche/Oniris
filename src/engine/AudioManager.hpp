#pragma once
#include <unordered_map>
#include <irrKlang/irrKlang.h>
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

	void Play(const std::string& path, float volume = 1.0f, bool loop = true);
	void Stop(const std::string& path);
	void SetListenerPosition(glm::vec3 position, glm::vec3 lookdir);
	void Init();


private:
	void SetUpSea();
	void SetUpRiver();
	void PlayWind();
	AudioManager() {};
	~AudioManager() {};
	irrklang::ISoundEngine* _Engine = irrklang::createIrrKlangDevice();
	void PlaySea(glm::vec3 position);
	void PlayWater(glm::vec3 position);
	void Play3D(const std::string& path, glm::vec3 position, float volume, float minDist = 0.0f );
};
