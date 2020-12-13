#include "Hud.hpp"

Hud::Hud()
{
	Panel panel1("res/img/uiplaceholder.png", "ui", 0.5, 0.5, 0.4, 1280, 1);
	_panels.push_back(panel1);

	Panel panel2("res/img/ui_inventory.png", "ui_inventory", 0.9, 0.3, 0.6, 93, 2);
	_panels.push_back(panel2);

	Panel panel3("res/img/ui_crystals.png", "ui_crystal", 0.8, -0.7, 1.5, 101, 5);
	_panels.push_back(panel3);
}

Hud::~Hud()
{
}

void Hud::Draw() const
{
	glDisable(GL_DEPTH_TEST);
	for (Panel panel : _panels) {
		panel.Draw();
	}
	glEnable(GL_DEPTH_TEST);
}

