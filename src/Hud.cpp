#include "Hud.hpp"
#include "Game.hpp"

void Hud::Init()
{
	Panel panel1("res/img/e_pickup.png", "e_pickup", 0.0, -0.9, 1.0, 288, 1, false);
	Panel panel2("res/img/e_observe.png", "e_observe", 0.0, -0.9, 1.0, 288, 1, false);
	Panel panel3("res/img/ui_crystal.png", "ui_crystal", 0.8, -0.7, 1.0, 128, 5, true);
	Panel panel4("res/img/ui_health.png", "ui_health", 0.8, -0.7, 1.0, 128, 9, true);
	Panel panel5("res/img/inv_key.png", "inv_key", 0.9, -0.1, 0.6, 128, 3, true);
	Panel panel6("res/img/inv_map.png", "inv_map", 0.9, -0.3, 0.6, 128, 3, true);
	Panel panel7("res/img/background.png", "background", 0, 0, 1, 1280, 1, false);

	_panels.insert({ "pickup", panel1 });
	_panels.insert({ "oberve", panel2 });
	_panels.insert({ "crystal", panel3 });
	_panels.insert({ "health", panel4 });
	_panels.insert({ "key", panel5 });
	_panels.insert({ "map", panel6 });
	_panels.insert({ "background", panel7 });

}


void Hud::Update()
{
	for (auto& pairs : _panels)
	{
		pairs.second.setVisibility(false);
	}

	if (_state != ScreenState::OBJMENU)
	{
		_panels.find("health")->second.setVisibility(true);
		_panels.find("crystal")->second.setVisibility(true);
		_panels.find("key")->second.setVisibility(true);
		_panels.find("map")->second.setVisibility(true);
	}
	else
	{
		_panels.find("background")->second.setVisibility(true);
	}
	
}


void Hud::Draw() const
{
	glDisable(GL_DEPTH_TEST);
	for (const std::pair<std::string,Panel> panelPair : _panels) {
		if (panelPair.second.IsVisible()) {
			panelPair.second.Draw();
		}
	}
	glEnable(GL_DEPTH_TEST);

	// Disable interactive panels
	//Hud::Get().SetVisibility("use", false);
}

void Hud::Scroll(int dir) {

	if (Game::Get().HasKey())
	{
		auto key = _panels.find("key");
		if (key != _panels.end()) 
			key->second.TranslateTexture(dir);
	}	
	if (Game::Get().Hasmap())
	{
		auto map = _panels.find("map");
		if (map != _panels.end()) 
			map->second.TranslateTexture(dir);
	}


	//_panels["key"].TranslateTexture(dir);
	//_panels["map"].TranslateTexture(dir);
}


void Hud::AddPanel(const std::string& name, const Panel& panel) {
	_panels.insert({ name, panel });

}

void Hud::SetVisibility(const std::string& name, bool visibility) {
	_panels.find(name)->second.setVisibility(visibility);
}