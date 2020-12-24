#include "Hud.hpp"
#include "Game.hpp"

#include <string>


void Hud::Init()
{
	std::vector<Panel> panels = {
		Panel("res/img/e_pickup.png", "p_pickup", 0.0, -0.9, 0.5, 288, 1, false),
		Panel("res/img/e_observe.png", "p_observe", 0.0, -0.9, 0.5, 288, 1, false),
		Panel("res/img/e_allumer.png", "p_lightup", 0.0, -0.9, 0.5, 288, 1, false),
		Panel("res/img/e_ouvrir.png", "p_open", 0.0, -0.9, 0.5, 288, 1, false),
		Panel("res/img/e_lightoff.png", "p_lightoff", 0.0, -0.9, 0.5, 288, 1, false),
		Panel("res/img/ui_crystal.png", "p_crystal", 0.8, -0.7, 1.0, 128, 5, true),
		Panel("res/img/ui_health.png", "p_health", 0.811, -0.7, 1.0, 128, 8, true),
		Panel("res/img/inv_key.png", "p_key", 0.9, 0.1, 0.4, 128, 3, true),
		Panel("res/img/inv_map.png", "p_map", 0.9, -0.1, 0.4, 128, 3, true),
		Panel("res/img/object/menuNarrativeObject.png", "p_menuNarrativeObject", 0, 0, 1, 1280, 1, false)
	};

	for (const Panel& panel : panels)
		AddPanel( panel.GetName() , panel );
}


void Hud::Update()
{
	for (auto& pairs : _panels)
	{
		pairs.second.setVisibility(false);
	}

	if (_state == ScreenState::OBJMENU)
	{
		_panels.find("p_menuNarrativeObject")->second.setVisibility(true);
	}
	else
	{
		_panels.find("p_health")->second.setVisibility(true);
		_panels.find("p_crystal")->second.setVisibility(true);
		_panels.find("p_key")->second.setVisibility(true);
		_panels.find("p_map")->second.setVisibility(true);
	}

}


void Hud::Draw() const 
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (const std::string& pname : _insertionOrder) {
		if (_panels.find(pname)->second.IsVisible()) {
			_panels.find(pname)->second.Draw();
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

}

void Hud::Scroll(int dir) {

	if (Game::Get().HasKey())
	{
		auto key = _panels.find("p_key");
		if (key != _panels.end()) 
			key->second.TranslateTexture(dir);
	}	
	if (Game::Get().Hasmap())
	{
		auto map = _panels.find("p_map");
		if (map != _panels.end()) 
			map->second.TranslateTexture(dir);
	}


	//_panels["key"].TranslateTexture(dir);
	//_panels["map"].TranslateTexture(dir);
}


void Hud::AddPanel(const std::string& name, const Panel& panel) {
	_insertionOrder.push_back(name);
	_panels.insert({ name, panel });

}

void Hud::SetVisibility(const std::string& name, bool visibility) {
	_panels.find(name)->second.setVisibility(visibility);
}

bool Hud::IsVisible(const std::string& name) const
{ 
	auto it = _panels.find(name);

	if (it != _panels.end())
		return it->second.IsVisible();
	else
		throw std::string("Panel name : " + name + " doesn't exist.");

	// Todo : réparer l'exception

	return false;
}