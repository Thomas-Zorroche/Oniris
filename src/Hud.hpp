#pragma once

#include "Panel.hpp"
#include "ResourceManager.hpp"


class Hud
{
public:
	Hud();
	~Hud();
	void Hud::Draw() const;

private:
	std::vector<Panel> _panels;
};

