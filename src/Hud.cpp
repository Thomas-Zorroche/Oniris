#include "Hud.hpp"

Hud::Hud()
{
	Panel panel1("res/img/uiplaceholder.png", "ui", 0.5, 0.5, 0.4);
	_panels.push_back(panel1);

	Panel panel2("res/img/ui_inventory.png", "ui_inventory", 0.9, 0.0, 1.0);
	_panels.push_back(panel2);
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

