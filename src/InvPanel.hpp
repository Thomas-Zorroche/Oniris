#pragma once

#include "Panel.hpp"

class InventoryPanel : public Panel
{
public:
	InventoryPanel(const std::string& texture,const std::string& name,float x,float y,float scale,int spriteSize,	int nbSprite,bool visibity)
		: Panel(texture, name, x, y, scale, spriteSize, nbSprite, visibity) {};
	void TranslateTexture(int dir) 
	{
		if (_position == 0)
		{
			Panel::TranslateTexture(dir);
			_position = 1;
		}
		else if (_position == 1)
		{
			Panel::TranslateTexture(dir);
			_position = 2;
		}
		else 
		{
			Panel::TranslateTexture(dir);
			Panel::TranslateTexture(dir);
			_position = 1;
		}
	};
private :
	int _position = 0;

};