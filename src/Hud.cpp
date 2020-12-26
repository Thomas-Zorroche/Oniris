#include "Hud.hpp"
#include "Game.hpp"
#include "InvPanel.hpp"

#include <string>


void Hud::Init()
{

	AddPanel("p_key", std::make_shared<InventoryPanel>("res/img/inv_key.png", "p_key", 0.9, 0.1, 0.4, 128, 3, true));
	AddPanel("p_map", std::make_shared<InventoryPanel>("res/img/inv_map.png", "p_map", 0.9, -0.1, 0.4, 128, 3, true));
	AddPanel("p_pickup", std::make_shared<Panel>("res/img/e_pickup.png", "p_pickup", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_observe", std::make_shared<Panel>("res/img/e_observe.png", "p_observe", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_lightup", std::make_shared<Panel>("res/img/e_allumer.png", "p_lightup", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_open", std::make_shared<Panel>("res/img/e_ouvrir.png", "p_open", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_lightoff", std::make_shared<Panel>("res/img/e_lightoff.png", "p_lightoff", 0.0, -0.9, 0.5, 288, 1, false));
	AddPanel("p_crystal", std::make_shared<Panel>("res/img/ui_crystal.png", "p_crystal", 0.8, -0.7, 1.0, 128, 5, true));
	AddPanel("p_health", std::make_shared<Panel>("res/img/ui_health.png", "p_health", 0.811, -0.7, 1.0, 128, 8, true));
	AddPanel("p_menuNarrativeObject", std::make_shared<Panel>("res/img/object/menuNarrativeObject.png", "p_menuNarrativeObject", 0, 0, 1, 1280, 1, false));
	AddPanel("p_menuMap", std::make_shared<Panel>("res/img/mapmenu.png", "p_menuMap", 0, 0, 1, 1280, 1, false));

}


void Hud::Update()
{
	for (auto& pairs : _panels)
	{
		pairs.second->setVisibility(false);
	}

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
		_panels.find("p_health")->second->setVisibility(true);
		_panels.find("p_crystal")->second->setVisibility(true);
	}

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


void Hud::Translate(const std::string& name) {

	if (name == "key")
	{
		auto key = _panels.find("p_key");
		if (key != _panels.end())
		{
			auto panel = (key->second);
			//auto panelinv = std::make_shared<InventoryPanel>(panel);
			panel->TranslateTexture(1);
		}
		Game::Get().LostKey();
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

	//_panels["key"].TranslateTexture(dir);
	//_panels["map"].TranslateTexture(dir);
}


void Hud::AddPanel(const std::string& name, const std::shared_ptr<Panel>& panel) {
	_insertionOrder.push_back(name);
	_panels.insert({ name, panel });

}

void Hud::SetVisibility(const std::string& name, bool visibility) {
	_panels.find(name)->second->setVisibility(visibility);
}

bool Hud::IsVisible(const std::string& name) const
{ 
	auto it = _panels.find(name);

	if (it != _panels.end())
		return it->second->IsVisible();
	else
		throw std::string("Panel name : " + name + " doesn't exist.");

	// Todo : r�parer l'exception

	return false;
}