#pragma once

#include <vector>
#include <memory>

#include "BaseLight.hpp"
#include "Shader.h"

class PointLight;
class DirectionalLight;

class LightManager
{
public:
	static LightManager& Get()
	{
		static LightManager instance;
		return instance;
	}
	LightManager(const LightManager&) = delete;
	LightManager& operator=(const LightManager&) = delete;

	void AddLight(const BaseLightPtr& light, LightType type);
	void AddPointLight(const BaseLightPtr& light);
	void AddDirLight(const BaseLightPtr& light);

	void SendUniforms(const std::shared_ptr<Shader>& shader);

	// Interactions
	void SwitchLights();


private:
	LightManager() = default;
	~LightManager() = default;

	std::vector<BaseLightPtr> _lights;

	unsigned int _pointLightsCount = 0;
	unsigned int _dirLightsCount = 0;

	bool _lightsOn = true;
};

