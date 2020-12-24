#pragma once

#include "Panel.hpp"
#include "ResourceManager.hpp"
#include <unordered_map>
#include <list>

enum class ScreenState
{
	INGAME = 0,	OVERLAP_O, OVERLAP_IO, OBJMENU
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

	void Draw() const;
	void Scroll(int dir);
	void Init();
	void AddPanel(const std::string& name, const Panel& panel);
	void SetVisibility(const std::string& name, bool visibility);
	bool IsVisible(const std::string& name) const; 
	void Update();
	ScreenState GetState() const { return _state; }
	void SetState(ScreenState state) { _state = state; }

private:
	Hud() = default;
	~Hud() = default ;
	std::unordered_map<std::string, Panel> _panels;
	std::list<std::string> _insertionOrder;
	ScreenState _state = ScreenState::INGAME;

};

