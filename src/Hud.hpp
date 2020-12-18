#pragma once

#include "Panel.hpp"
#include "ResourceManager.hpp"


class Hud
{
public:
	Hud();
	~Hud();
	void Hud::Draw() const;
	void Hud::Scroll(int dir);

private:
	std::unordered_map<std::string, Panel> _panels;
};

