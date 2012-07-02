#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>

#include "mysprite.h"
#include "enemy.cpp"
#include "player.cpp"
#include "mystring.cpp"
#include "mycamera.cpp"

using namespace std;

bool Movement(vector<Enemy>& enemies, Player UFO, MyCamera MainCam);
void endGame(sf::RenderWindow& App, MyCamera MainCamera);

int main()
{
	srand(time(NULL));
	
	//Create window and event handler
	sf::RenderWindow App(sf::VideoMode(800,600),"Views");
	sf::Event Event;
	
	//construct ufo object (main player)
	Player UFO;
	
	//construct sprites/container
	MySprite laser("data/laser.png");
	std::list <MySprite> laser_container;
	//MySprite background("data/space.gif");
	
	//Create enemy and container for enemies
	Enemy main;
	vector <Enemy> enemies;
	
	//Create strings to display various items
	MyString health("Health: ",100, sf::Color(0,238,0));
	MyString score("Score: ",0, sf::Color(0,0,238));
	MyString time_passed("Time: ",0, sf::Color(255,193,37));
	MyString s_speed("Speed: ",1,sf::Color(220,20,60));
	
	//Construct main camera
	MyCamera MainCam(sf::Vector2f(800,600),1);

	//Create clocks
	sf::Clock GameTime;
	sf::Clock c_time;
	sf::Clock c_enemyspawn;

	while (App.isOpen())
	{
		while (App.pollEvent(Event))
		{
			switch (Event.type)
			{
				case sf::Event::Closed:
					App.close();
					break;
					
				default:
					break;
			}
		}
		float factor = GameTime.restart().asSeconds();
		App.clear();
		//Updates Time
		time_passed.str.setString("Time: "+time_passed.UpdateString(time_passed.ss,c_time.getElapsedTime().asSeconds()));
		//Starts moving camera
		MainCam.MoveCamera(App);
		//Sets ufo to move with camera
		UFO.pl.move(MainCam.speed,0);
		
		//Sets texts to move with camera
		score.str.setPosition(MainCam.Center().x-395,0);
		health.str.setPosition(MainCam.Center().x-200,0);
		time_passed.str.setPosition(MainCam.Center().x+15,0);
		s_speed.str.setString("Speed: "+s_speed.UpdateString(s_speed.ss, MainCam.speed));
		s_speed.str.setPosition(MainCam.Center().x+235,0);
	
	
		if (c_enemyspawn.getElapsedTime().asSeconds() >= 1.f)
		{
			main.SetRand(MainCam.Center());
			enemies.push_back(main);
			c_enemyspawn.restart();
		}
	
	
		//draw background(in development)
		//App.draw(background.spr);
		
	
		//draw text to screen
		App.draw(health.str);
		App.draw(score.str);
		App.draw(time_passed.str);
		App.draw(s_speed.str);
		
		//Player Movement
		UFO.MoveDirection(App, MainCam, Event, factor);
		
		//Collision between laser/enemy
		if (UFO.FireLasers(App, laser, laser_container, MainCam, enemies, Event))
		{
			score.str.setString("Score: "+score.UpdateString(1,true));
		}
		
		//Move enemies+Collision between player/enemy
		if (Movement(enemies,UFO, MainCam)) 
		{
			health.str.setString("Health: "+health.UpdateString(10,false));
			if (health.initNum <= 0) 
			{
				endGame(App, MainCam);
				break;
			}
		}
		
		//Display invaders
		for (unsigned int tmp=0; tmp<enemies.size(); tmp++) 
		{
			App.draw(enemies[tmp].inv);
		}
		
		//display everything drawn
		App.display();
	}
		
	return EXIT_SUCCESS;
}


bool Movement(vector<Enemy>& enemies, Player UFO, MyCamera MainCam)
{
	for (unsigned int en=0; en<enemies.size(); en++)
	{		
		if (enemies[en].AbleToMove) enemies[en].inv.move(-10,0);
		enemies[en].inv_newX = enemies[en].inv.getPosition().x;
		enemies[en].inv_newY = enemies[en].inv.getPosition().y;
		
		if ( (UFO.pl_newX+UFO.pl_imgW >= enemies[en].inv_newX && UFO.pl_newX+UFO.pl_imgW <= enemies[en].inv_newX+enemies[en].inv_imgW) && (((UFO.pl_newY <= enemies[en].inv_newY+enemies[en].inv_imgH) && (UFO.pl_newY+UFO.pl_imgH >= enemies[en].inv_newY+enemies[en].inv_imgH)) || ((UFO.pl_newY+UFO.pl_imgH >= enemies[en].inv_newY) && (UFO.pl_newY+UFO.pl_imgH <= enemies[en].inv_newY+enemies[en].inv_imgH))))
		
		{
			enemies.erase(enemies.begin()+en);
			return true;
		}
		
		if (enemies[en].inv_newX <= MainCam.Center().x-400-enemies[en].inv_imgW) enemies.erase(enemies.begin()+en);
	}
	return false;
}

void endGame(sf::RenderWindow& App, MyCamera MainCam)
{
	App.clear();
	MyString end("Game is over!",MainCam.Center().x-80,MainCam.Center().y, sf::Color(255,69,0));
	//end.str.SetColor(sf::Color(255,69,0));
	App.draw(end.str);
	App.display();
	sleep(5);
}
