#include "Hud.hpp"
#include "Game.hpp"
#include "InvPanel.hpp"
#include "TargetPanel.hpp"

#include <string>
#include <iostream>


void Hud::Init()
{

	AddPanel("p_key", std::make_shared<InventoryPanel>("res/img/hud/inv_key.png", "p_key", 0.9, 0.1, 0.4, 128, 3, true));
	AddPanel("p_map", std::make_shared<InventoryPanel>("res/img/hud/inv_map.png", "p_map", 0.9, -0.1, 0.4, 128, 3, true));
	AddPanel("p_pickup", std::make_shared<Panel>("res/img/hud/e_pickup.png", "p_pickup", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_observe", std::make_shared<Panel>("res/img/hud/e_observe.png", "p_observe", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_lightup", std::make_shared<Panel>("res/img/hud/e_lighton.png", "p_lightup", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_open", std::make_shared<Panel>("res/img/hud/e_open.png", "p_open", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_close", std::make_shared<Panel>("res/img/hud/e_close.png", "p_close", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_lightoff", std::make_shared<Panel>("res/img/hud/e_lightoff.png", "p_lightoff", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_crystal", std::make_shared<Panel>("res/img/hud/ui_crystal.png", "p_crystal", 0.8, -0.7, 1.0, 128, 5, true));
	AddPanel("p_menuNarrativeObject", std::make_shared<Panel>("res/img/object/menuNarrativeObject.png", "p_menuNarrativeObject", 0, 0, 1, 1280, 1, false));
	AddPanel("p_menuMap", std::make_shared<Panel>("res/img/hud/mapmenu.png", "p_menuMap", 0, 0, 1, 1280, 1, false));
	AddPanel("p_target", std::make_shared<TargetPanel>("res/img/hud/target.png", "p_target", 0, 0, 1.0, 8, 2, true));

}


void Hud::Update()
{
	// Initialisation ==================================

	for (auto& pairs : _panels)
	{
		pairs.second->setVisibility(false);
	}
	SetTarget(0);

	// ==================================================

	if (_state == ScreenState::OBJMENU)
	{
		_panels.find("p_menuNarrativeObject")->second->setVisibility(true);
	}
	else if (_state == ScreenState::MAPMENU)
	{
		_panels.find("p_menuMap")->second->setVisibility(true);

	}
	else
	{
		_panels.find("p_key")->second->setVisibility(true);
		_panels.find("p_map")->second->setVisibility(true);
		_panels.find("p_crystal")->second->setVisibility(true);
		_panels.find("p_target")->second->setVisibility(true);
	}

	//_state = ScreenState::INGAME;
}


void Hud::Draw() const 
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (const std::string& pname : _insertionOrder) {
		if (_panels.find(pname)->second->IsVisible()) {
			_panels.find(pname)->second->Draw();
		}
	}


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

}


void Hud::Translate(const std::string& name, const std::shared_ptr<Game>& game) {

	if (name == "key")
	{
		auto key = _panels.find("p_key");
		if (key != _panels.end())
		{
			auto panel = (key->second);
			panel->TranslateTexture(1);
		}
		game->LostKey();
	}
	else if (name == "map")
	{
		auto map = _panels.find("p_map");
		if (map != _panels.end()) 
			map->second->TranslateTexture(1);
	}
	else
	{
		auto panel = _panels.find("p_"+ name);
		if (panel != _panels.end())
			panel->second->TranslateTexture(1);
	}
}


void Hud::AddPanel(const std::string& name, const std::shared_ptr<Panel>& panel) {
	_insertionOrder.push_back(name);
	_panels.insert({ name, panel });

}

void Hud::SetVisibility(const std::string& name, bool visibility) {
	_panels.find(name)->second->setVisibility(visibility);
}

