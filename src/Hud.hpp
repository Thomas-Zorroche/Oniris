#pragma once

#include "Panel.hpp"
#include "ResourceManager.hpp"
#include <unordered_map>
#include <list>

/*
* OVERLAP_NO = When overlap Narrative Object
* OVERLAP_UO = When overlap Usable Object
* OVERLAP_IO = When overlap Interactive Object
* OBJMENU    = When observe Narrative Object
* MAPMENU    = When observe Map
*/
enum class ScreenState
{
	INGAME = 0,	OVERLAP_NO, OVERLAP_UO, OVERLAP_IO, OBJMENU, MAPMENU
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
	void Translate(const std::string& name);
	void Init();
	void AddPanel(const std::string& name, const std::shared_ptr<Panel>& panel);
	void SetVisibility(const std::string& name, bool visibility);
	bool IsVisible(const std::string& name) const; 
	void Update();
	ScreenState GetState() const { return _state; }
	void SetState(ScreenState state) { _state = state; }
	void SetTarget(int position) { _panels.find("p_target")->second->TranslateTexture(position); }

private:
	Hud() = default;
	~Hud() = default ;
	std::unordered_map<std::string, std::shared_ptr<Panel>> _panels;
	std::list<std::string> _insertionOrder;
	ScreenState _state = ScreenState::INGAME;
	bool _changeTargetSprite = true;

};

