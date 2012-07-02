#ifndef MYSPRITE_H
#define MYSPRITE_H

#include <SFML/Graphics.hpp>

struct MySprite
{
	MySprite(const char* imgPath)
	{
		img.loadFromFile(imgPath);
		img_w = img.getSize().x;
		img_h = img.getSize().y;
		spr.setTexture(img);
	}	
	sf::Texture img;
	sf::Sprite spr;
	int img_w;
	int img_h;
	float posX;
	float posY;
	
};

#endif
