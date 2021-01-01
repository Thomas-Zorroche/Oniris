#pragma once

#include "Portal.hpp"
#include "glm/glm.hpp"
#include "StaticMesh.hpp"

class Game
{
public:
	Game();

	void PickUp(const std::string& type);
	void PassThroughGate();

	void LostKey() { _HasKey = false; };
	bool HasKey() const { return _HasKey; };
	bool Hasmap() const { return _HasMap; };

	std::shared_ptr<Portal> PortalPtr() { return _portal; }

	
private:
	bool _HasKey = false;
	bool _HasMap = false;

	int _crystalCount = 0;
	bool _darkWorld = false;

	std::shared_ptr<Portal> _portal;
};
