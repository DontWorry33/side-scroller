#include "player.h"

Player::Player()
{
	pl_img.loadFromFile("data/ufo.png");
	pl_imgH = pl_img.getSize().x;
	pl_imgW = pl_img.getSize().y;
	pl.setTexture(pl_img);
}

void Player::MoveDirection(sf::RenderWindow& App, MyCamera MainCam, sf::Event& Event, float factor)
{
	
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	 {
		if (pl_newX <= MainCam.Center().x-400) pl_newX=pl_newX;
		else pl.move(-factor*400,0);
	 }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (pl_newX+pl_imgW >= MainCam.Center().x+400) pl_newX=pl_newX;
		else pl.move(factor*400,0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (pl_newY <= 0.f) pl_newY=pl_newY;
		else pl.move(0,-factor*400);	
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (pl_newY+pl_imgH >= 600.f) pl_newY=pl_newY;
		else pl.move(0,factor*400);		
	}
	
	pl_newX = pl.getPosition().x;
	pl_newY = pl.getPosition().y;
	App.draw(pl);
}

bool Player::FireLasers(sf::RenderWindow& App, MySprite laser, 
						std::list<MySprite>& laser_container,
						MyCamera MainCam, std::vector<Enemy>& enemies,
						sf::Event& Event)
{

	if (laser_container.size() > 10)
	{
		MyString temp("TOO MANY LASERS ON SCREEN", sf::Color(122,139,139));
		temp.str.setPosition(MainCam.Center().x-160,30);
		App.draw(temp.str);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		laser.spr.setPosition(pl_newX+(pl_imgW/2),pl_newY+(pl_imgH/2));
		if (laser_container.size() <= 10) laser_container.push_back(laser);
	}
			
	for (auto it=laser_container.begin(); it!=laser_container.end() ; it++)
	{
		it->spr.move(MainCam.speed,0);
		it->spr.move(15,0);
		
		it->posX = it->spr.getPosition().x;
		it->posY = it->spr.getPosition().y;		
		App.draw(it->spr);
		
		for (unsigned int en=0; en<enemies.size(); en++)
		{
			if (
			(it->posX+it->img_w >= enemies[en].inv_newX && it->posX+it->img_w <= enemies[en].inv_newX+enemies[en].inv_imgW) &&
			
			(((it->posY <= enemies[en].inv_newY+enemies[en].inv_imgH) && (it->posY+it->img_h >= enemies[en].inv_newY+enemies[en].inv_imgH))||
			((it->posY+it->img_h >= enemies[en].inv_newY) && (it->posY+it->img_h <= enemies[en].inv_newY+enemies[en].inv_imgH)))
			)
			{
				enemies.erase(enemies.begin()+en);
				return true;
			}
						
		}
		if (it->posX >= MainCam.Center().x+400) 
		{
			auto tmp_it(it);
			tmp_it--;
			laser_container.erase(it);
			it=tmp_it;
		}

	}
	return false;
}
