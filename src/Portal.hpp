#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "StaticMesh.hpp"
#include "Model.hpp"
#include "Fog.hpp"


class Portal
{
public:
	Portal();
	
	void Open();

	void Draw();

	void HitCBox();

	void SetFog(const std::shared_ptr<Fog>& fog);

private:
	bool _open = false;
	bool _canEnter = false;

	int _hitsCountCBox = 0;

	StaticMesh _staticMesh;
	std::shared_ptr<Fog> _fog = nullptr;

	bool _darkWorld = false;
};

