#pragma once

#include <vector>
#include <memory>

#include "lighting/BaseLight.hpp"
#include "opengl/Shader.h"
#include "gameplay/CreateCrystal.hpp"


class PointLight;
class DirectionalLight;
class Terrain;
class Portal;

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

	void LoadAllLights(const std::shared_ptr<Terrain>& terrain, const std::shared_ptr<Portal>& portal, const CreateCrystal& crystal);

	void SendUniforms(const std::shared_ptr<Shader>& shader);

	// Interactions
	void SwitchLights();


private:
	LightManager() = default;
	~LightManager() = default;

	const static int POINT_LIGHTS_COUNT;

	std::vector<BaseLightPtr> _lights;

	unsigned int _pointLightsCount = 0;
	unsigned int _dirLightsCount = 0;

	bool _lightsOn = false;
};

