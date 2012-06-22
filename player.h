#ifndef PLAYER_H
#define PLAYER_H

#include "mysprite.h"
#include "mycamera.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

struct Player
{
	Player();
	void MoveDirection(sf::RenderWindow&, MyCamera MainCam);
	bool FireLasers(sf::RenderWindow& App, MySprite laser, 
	std::list<MySprite>& laser_container,
	MyCamera MainCam,
	std::vector<Enemy>& enemies);
	
	float pl_newX;
	float pl_newY;
	
	float pl_imgH;
	float pl_imgW;
	
	sf::Vector2f lz_pos;
	
	sf::Sprite pl;
	sf::Image pl_img;
	
};

#endif
