#ifndef MYSPRITE_H
#define MYSPRITE_H

#include <SFML/Graphics.hpp>

struct MySprite
{
	MySprite(const char* imgPath)
	{
		img.LoadFromFile(imgPath);
		img_w = img.GetWidth();
		img_h = img.GetHeight();
		spr.SetImage(img);
	}	
	sf::Image img;
	sf::Sprite spr;
	int img_w;
	int img_h;
	float posX;
	float posY;
	
};

#endif
