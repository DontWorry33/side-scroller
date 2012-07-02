#include "enemy.h"

Enemy::Enemy()
{
	tm=0.f;
	
	explode=false;
	AbleToMove=true;
	markHit=false;
	score_b=true;
	
	inv_initX = 0;
	inv_initY = 0;
	
	if (!inv_i.loadFromFile("data/ufo2.png")) std::cout << "Failed to load Image" << std::endl;
	//else std::cout << "Image loaded" << std::endl;
	inv_imgW = inv_i.getSize().x;
	inv_imgH = inv_i.getSize().y;
	std::cout << inv_imgH << std::endl;
	inv.setTexture(inv_i);
}

double Enemy::randrange(double from, double to)
{
	double tmp=to-from;
	return ((double)rand())/RAND_MAX*tmp+from;
}

void Enemy::SetRand(sf::Vector2f cent)
{
	int max_bnd = cent.x+(400-inv_imgW);
	int max_h = 600-inv_imgH;
	inv_initX=randrange(max_bnd,max_bnd+100);
	inv_initY=randrange(1,max_h);
	inv.setPosition(inv_initX, inv_initY);
}

//pl_newX/Y
//inv_newX/Y
//pl_imgH/W
//inv_imgH/W
