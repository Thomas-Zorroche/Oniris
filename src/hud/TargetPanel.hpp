#pragma once

#include "hud/Panel.hpp"

class TargetPanel : public Panel
{
public:
	TargetPanel(const std::string& texture, const std::string& name, float x, float y, float scale, int spriteSize, int nbSprite, bool visibity)
		: Panel(texture, name, x, y, scale, spriteSize, nbSprite, visibity) {};
	void TranslateTexture( int pos ) // 0 = 50% opacity ; 1 = 100% opacity
	{
		if (_texturePosition == 0)
		{
			if (pos == 1)
			{
				Panel::TranslateTexture(1);
				_texturePosition = 1;
			}
		} else {
			if (pos == 0) {
				Panel::TranslateTexture(1);
				_texturePosition = 0;
			}
		}
	};
private:
	int _texturePosition = 0;

};
