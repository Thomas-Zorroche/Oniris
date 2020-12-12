#include "Hud.hpp"

Hud::Hud()
{
	Panel newpanel("res/img/uiplaceholder.png", "ui", 0.5,0.5,0.4);
	_panels.push_back(newpanel);
}

Hud::~Hud()
{
}

void Hud::Draw() const
{
	for (Panel panel : _panels) {
		panel.Draw();
	}
}

