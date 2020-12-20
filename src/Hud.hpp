#pragma once

#include "Panel.hpp"
#include "ResourceManager.hpp"


class Hud
{
public:
	static Hud& Get()
	{
		static Hud instance;
		return instance;
	}

	Hud(const Hud&) = delete;
	Hud& operator=(const Hud&) = delete;

	void Hud::Draw() const;
	void Hud::Scroll(int dir);
	void Hud::Init();
	void Hud::AddPanel(const std::string& name, const Panel& panel);
	void Hud::SetVisible(const std::string& name);


private:
	Hud() = default;
	~Hud() = default ;
	std::unordered_map<std::string, Panel> _panels;
};

