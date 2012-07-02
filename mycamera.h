#ifndef MYCAMERA_H
#define MYCAMERA_H
#include <SFML/Graphics.hpp>
#include "mystring.h"

struct MyCamera
{
	MyCamera(sf::Vector2f attr, int startspeed);
	void MoveCamera(sf::RenderWindow& App);
	sf::Vector2f Center();
	void SpeedUp(unsigned int xRange, unsigned int spd);	
	int speed;
	sf::Vector2f init_Center;
	sf::Vector2f init_HalfSize;
	sf::View MainView;
};

#endif

