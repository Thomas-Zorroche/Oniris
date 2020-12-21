#pragma once

#include "Panel.hpp"
#include "ResourceManager.hpp"

enum class ScreenState
{
	INGAME = 0,	ONOVERLAP, OBJMENU
};

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
	void Hud::SetVisibility(const std::string& name, bool visibility);
	bool Hud::IsVisible(const std::string& name) { return _panels.find(name)->second.IsVisible(); };
	void Hud::Update();

private:
	Hud() = default;
	~Hud() = default ;
	std::unordered_map<std::string, Panel> _panels;

	ScreenState _state = ScreenState::INGAME;
};

