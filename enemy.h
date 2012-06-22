#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
//#include "player.h"

struct Enemy
{
	Enemy();
	void SetRand(sf::Vector2f cent);
	double randrange(double, double);
	//void Movement(Enemy main, Player& UFO);

	float inv_initX;
	float inv_initY;
	
	float inv_newX;
	float inv_newY;
	
	int inv_imgW;
	int inv_imgH;
	
	bool explode;
	bool AbleToMove;
	bool markHit;
	bool score_b;
	float tm;
	
	sf::Sprite inv;
	sf::Image inv_i;
};

#endif
