#pragma once

#include "Panel.hpp"

class InventoryPanel : public Panel
{
public:
	InventoryPanel(const std::string& texture,const std::string& name,float x,float y,float scale,int spriteSize,	int nbSprite,bool visibity)
		: Panel(texture, name, x, y, scale, spriteSize, nbSprite, visibity) {};
	void TranslateTexture(int dir) 
	{
		if (_texturePosition == 0)
		{
			Panel::TranslateTexture(dir);
			_texturePosition = 1;
		}
		else if (_texturePosition == 1)
		{
			Panel::TranslateTexture(dir);
			_texturePosition = 2;
		}
		else 
		{
			Panel::TranslateTexture(dir);
			Panel::TranslateTexture(dir);
			_texturePosition = 1;
		}
	};
private :
	int _texturePosition = 0;

};