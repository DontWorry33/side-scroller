#include "player.h"

Player::Player()
{
	pl_img.LoadFromFile("data/ufo.png");
	pl_imgH = pl_img.GetHeight();
	pl_imgW = pl_img.GetWidth();
	pl.SetImage(pl_img);
}

void Player::MoveDirection(sf::RenderWindow& App, MyCamera MainCam)
{
	float factor(App.GetFrameTime());

	if (App.GetInput().IsKeyDown(sf::Key::Right))
	{
		if (pl_newX+pl_imgW >= MainCam.Center().x+400) pl_newX=pl_newX;
		else pl.Move(factor*400,0);
	}
	if (App.GetInput().IsKeyDown(sf::Key::Left))
	{
		if (pl_newX <= MainCam.Center().x-400) pl_newX=pl_newX;
		else pl.Move(-factor*400,0);
	}
	if (App.GetInput().IsKeyDown(sf::Key::Up))
	{
		if (pl_newY <= 0.f) pl_newY=pl_newY;
		else pl.Move(0,-factor*400);
	}
	if (App.GetInput().IsKeyDown(sf::Key::Down))
	{
		if (pl_newY+pl_imgH >= 600.f) pl_newY=pl_newY;
		else pl.Move(0,factor*400);
	}
	pl_newX = pl.GetPosition().x;
	pl_newY = pl.GetPosition().y;
	App.Draw(pl);
}

bool Player::FireLasers(sf::RenderWindow& App, MySprite laser, 
						std::list<MySprite>& laser_container,
						MyCamera MainCam, std::vector<Enemy>& enemies)
{
	if (App.GetInput().IsKeyDown(sf::Key::Space))
	{
		laser.spr.SetPosition(pl_newX+(pl_imgW/2),pl_newY+(pl_imgH/2));
		laser_container.push_back(laser);
		
	}
	
	for (auto it=laser_container.begin(); it!=laser_container.end() ; it++)
	{
		it->spr.Move(MainCam.speed,0);
		it->spr.Move(App.GetFrameTime()*500,0);
		
		it->posX = it->spr.GetPosition().x;
		it->posY = it->spr.GetPosition().y;		
		App.Draw(it->spr);
		
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
