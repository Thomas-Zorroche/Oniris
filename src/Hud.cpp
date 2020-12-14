#include "Hud.hpp"

Hud::Hud()
{
	Panel panel1("res/img/ui_use.png", "ui_use", 0.0, -0.9, 1.0, 132, 1, false);
	_panels.push_back(panel1);

	Panel panel2("res/img/ui_observe.png", "ui_observe", -0.3, -0.9, 1.0, 147, 1, false);
	_panels.push_back(panel2);

	Panel panel3("res/img/ui_crystal.png", "ui_crystal", 0.8, -0.7, 1.0, 163, 5, true);
	_panels.push_back(panel3);

	Panel panel4("res/img/ui_health.png", "ui_health", 0.8, -0.7, 1.0, 163, 8, true);
	_panels.push_back(panel4);

	Panel panel5("res/img/ui_key.png", "ui_key", 0.9, -0.1, 0.6, 80, 3, true);
	_panels.push_back(panel5);

	Panel panel6("res/img/ui_map.png", "ui_map", 0.9, -0.3, 0.6, 80, 3, true);
	_panels.push_back(panel6);

}

Hud::~Hud()
{
}

void Hud::Draw() const
{
	glDisable(GL_DEPTH_TEST);
	for (Panel panel : _panels) {
		if (panel.IsVisible()) {
			panel.Draw();
		}
	}
	glEnable(GL_DEPTH_TEST);
}

