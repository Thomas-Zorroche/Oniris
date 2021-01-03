#pragma once

#include <glm/glm.hpp>

#include "engine/StaticMesh.hpp"
#include "engine/Model.hpp"


class Fog;
class BaseLight;


class Portal
{
public:
	Portal();
	
	void Open();

	void Draw();

	void HitCBox();

	void SetFog(const std::shared_ptr<Fog>& fog);

	void SetLight(const std::shared_ptr<BaseLight>& light);

private:
	bool _open = true;
	bool _canEnter = false;

	int _hitsCountCBox = 0;

	StaticMesh _staticMesh;
	std::shared_ptr<Fog> _fog = nullptr;
	std::shared_ptr<BaseLight> _light = nullptr;

	bool _darkWorld = false;
};

