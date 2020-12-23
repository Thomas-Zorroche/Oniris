#pragma once

#include <vector>

#include "BaseLight.hpp"

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

	BaseLightPtr GetLight(int id) const;
	void AddLight(const BaseLightPtr& light);

	void InitMeshes();

private:
	LightManager() = default;
	~LightManager() = default;

	std::vector<BaseLight> _lights;
};

