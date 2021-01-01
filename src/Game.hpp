#pragma once

#include "Portal.hpp"
#include "glm/glm.hpp"
#include "StaticMesh.hpp"

class Game
{
public:
	static Game& Get()
	{
		static Game instance;
		return instance;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;


	void PickUp(const std::string& type) { 
		if (type == "key")
			_HasKey = true;
		else if (type == "map")
			_HasMap = true;
		else if (type == "crystal")
		{
			_crystalCount++;
			if (_crystalCount == 4)
			{
				_portal->Open();
			}
		}
	};

	void LostKey() { _HasKey = false; };
	bool HasKey() const { return _HasKey; };
	bool Hasmap() const { return _HasMap; };

	std::shared_ptr<Portal> PortalPtr() { return _portal; }

	void PassThroughGate()
	{
		if (_darkWorld)
			_darkWorld = false;
		else
			_darkWorld = true;
	}
	
private:

	Game() = default ;
	~Game() = default ;

	bool _HasKey = false;
	bool _HasMap = false;

	int _crystalCount = 0;
	bool _darkWorld = false;

	std::shared_ptr<Portal> _portal = std::make_shared<Portal>(Model("res/models/PortalPlan.obj"), 
															   TransformLayout(glm::vec3(499, 75, 578), glm::vec3(0, 0, 0), 2.2f));
};
