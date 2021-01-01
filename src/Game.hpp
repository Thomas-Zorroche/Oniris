#pragma once

#include "Portal.hpp"
#include "glm/glm.hpp"
#include "StaticMesh.hpp"
#include "CBoxPortal.hpp"

class Game
{
public:
	Game();

	void PickUp(const std::string& type);

	void LostKey() { _HasKey = false; };
	bool HasKey() const { return _HasKey; };
	bool Hasmap() const { return _HasMap; };

	std::shared_ptr<Portal> PortalPtr() { return _portal; }

	void SetFog(const std::shared_ptr<Fog>& fog) { _portal->SetFog(fog); }
	
private:
	bool _HasKey = false;
	bool _HasMap = false;

	// Portal Variables
	int _crystalCount = 0;
	std::shared_ptr<Portal> _portal;
	CBoxPortal _cBoxBack = CBoxPortal(Model("res/models/CBoxPortal.obj"), TransformLayout(glm::vec3(499, 78, 581), glm::vec3(0, 0, 0), 2.2f), _portal);
	CBoxPortal _cBoxFront = CBoxPortal(Model("res/models/CBoxPortal.obj"), TransformLayout(glm::vec3(499, 75, 575), glm::vec3(0, 0, 0), 2.2f), _portal);
};
