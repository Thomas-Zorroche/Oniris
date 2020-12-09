#pragma once
#include "Panel.hpp"
#include "ResourceManager.hpp"


class Hud
{
public:
	Hud();
	~Hud();

private:
	std::vector<Panel> _panels;
};

Hud::Hud()
{	
	//Panel newpanel(ResourceManager::Get().LoadTexture("res/img/placeholder.png", DIFFUSE));
	//_panels.push_back(newpanel);
}

Hud::~Hud()
{
}