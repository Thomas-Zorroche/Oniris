#include "Hud.hpp"

void Hud::Init()
{
	Panel panel1("res/img/ui_use.png", "ui_use", 0.0, -0.9, 1.0, 132, 1, false);
	Panel panel2("res/img/ui_observe.png", "ui_observe", -0.3, -0.9, 1.0, 147, 1, false);
	Panel panel3("res/img/ui_crystal.png", "ui_crystal", 0.8, -0.7, 1.0, 163, 5, true);
	Panel panel4("res/img/ui_health.png", "ui_health", 0.8, -0.7, 1.0, 163, 8, true);
	Panel panel5("res/img/ui_key.png", "ui_key", 0.9, -0.1, 0.6, 80, 3, true);
	Panel panel6("res/img/ui_map.png", "ui_map", 0.9, -0.3, 0.6, 80, 3, true);

	_panels.insert({ "use", panel1 });
	_panels.insert({ "observe", panel2 });
	_panels.insert({ "crystal", panel3 });
	_panels.insert({ "health", panel4 });
	_panels.insert({ "key", panel5 });
	_panels.insert({ "map", panel6});

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
}

void Hud::Scroll(int dir) {

	auto key = _panels.find("key");
	auto map = _panels.find("map");
	if (key != _panels.end() && map != _panels.end()) {
		key->second.TranslateTexture(dir);
		map->second.TranslateTexture(dir);
	}

	//_panels["key"].TranslateTexture(dir);
	//_panels["map"].TranslateTexture(dir);
}


void Hud::AddPanel(const std::string& name, const Panel& panel) {
	_panels.insert({ name, panel });

}

void Hud::SetVisible(const std::string& name) {
	_panels.find(name)->second.setVisible();
}