#pragma once

#include "Panel.hpp"

class InventoryPanel : public Panel
{
public:
	InventoryPanel(const std::string& texture,const std::string& name,float x,float y,float scale,int spriteSize,	int nbSprite,bool visibity)
		: Panel(texture, name, x, y, scale, spriteSize, nbSprite, visibity) {};
	void TranslateTexture(int dir) 
	{
		std::cout << "indice de translation  " << _translation << std::endl;
		if (_translation == 0)
		{
			Panel::TranslateTexture(dir);
			_translation = 1;
		}
		else if (_translation == 1)
		{
			Panel::TranslateTexture(dir);
			_translation = 2;
		}
		else 
		{
			Panel::TranslateTexture(dir);
			Panel::TranslateTexture(dir);
			_translation = 1;
		}
	};
private :
	int _translation = 0;

};