#pragma once

#include "Panel.hpp"

class TargetPanel : public Panel
{
public:
	TargetPanel(const std::string& texture, const std::string& name, float x, float y, float scale, int spriteSize, int nbSprite, bool visibity)
		: Panel(texture, name, x, y, scale, spriteSize, nbSprite, visibity) {};
	void TranslateTexture( int pos ) // 0 = 50% opacity ; 1 = 100% opacity
	{
		if (_position == 0)
		{
			if (pos == 1)
			{
				Panel::TranslateTexture(1);
				_position = 1;
			}
		} else {
			if (pos == 0) {
				Panel::TranslateTexture(1);
				_position = 0;
			}
		}
	};
private:
	int _position = 0;

};
