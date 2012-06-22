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
	
	//construct sprites
	MySprite laser("data/laser.png");
	std::list <MySprite> laser_container;
	MySprite background("data/background.jpg");
	
	//Create enemy and container for enemies
	Enemy main;
	vector <Enemy> enemies;
	
	//Create strings to display various items
	MyString health("Health: ",100, sf::Color(0,238,0));
	MyString score("Score: ",0, sf::Color(0,0,238));
	MyString time_passed("Time: ",0, sf::Color(255,193,37));
	MyString s_speed("Speed: ",1,sf::Color(220,20,60));
	
	//Set colors to strings
	//health.str.SetColor(sf::Color(0,238,0));
	//score.str.SetColor(sf::Color(0,0,238));
	//time_passed.str.SetColor(sf::Color(255,193,37));
	
	//Construct main camera
	MyCamera MainCam(sf::Vector2f(800,600),1);

	//Create clocks
	sf::Clock c_time;
	sf::Clock c_enemyspawn;

	while (App.IsOpened())
	{
		while (App.GetEvent(Event))
		{
			switch (Event.Type)
			{
				case sf::Event::Closed:
					App.Close();
					break;
					
				default:
					break;
			}
		}
		App.Clear();
		//Updates Time
		time_passed.str.SetText("Time: "+time_passed.UpdateString(time_passed.ss,c_time.GetElapsedTime()));
		//Starts moving camera
		MainCam.MoveCamera(App);
		//Sets ufo to move with camera
		UFO.pl.Move(MainCam.speed,0);
		
		//Sets texts to move with camera
		score.str.SetPosition(MainCam.Center().x-395,0);
		health.str.SetPosition(MainCam.Center().x-200,0);
		time_passed.str.SetPosition(MainCam.Center().x+15,0);
		s_speed.str.SetText("Speed: "+s_speed.UpdateString(s_speed.ss, MainCam.speed));
		s_speed.str.SetPosition(MainCam.Center().x+235,0);
	
	
		if (c_enemyspawn.GetElapsedTime() >= 1.f)
		{
			main.SetRand(MainCam.Center());
			enemies.push_back(main);
			c_enemyspawn.Reset();
		}
	
	
		//draw text to screen
		App.Draw(health.str);
		App.Draw(score.str);
		App.Draw(time_passed.str);
		App.Draw(s_speed.str);
		
		//Player Movement
		UFO.MoveDirection(App, MainCam);
		
		//Collision between laser/enemy
		if (UFO.FireLasers(App, laser, laser_container, MainCam, enemies))
		{
			score.str.SetText("Score: "+score.UpdateString(1,true));
		}
		
		//Move enemies+Collision between player/enemy
		if (Movement(enemies,UFO, MainCam)) 
		{
			health.str.SetText("Health: "+health.UpdateString(10,false));
			if (health.initNum <= 0) 
			{
				endGame(App, MainCam);
				break;
			}
		}
		
		//Display invaders
		for (unsigned int tmp=0; tmp<enemies.size(); tmp++) 
		{
			App.Draw(enemies[tmp].inv);
		}
		
		//display everything drawn
		App.Display();
	}
		
	return EXIT_SUCCESS;
}


bool Movement(vector<Enemy>& enemies, Player UFO, MyCamera MainCam)
{
	for (unsigned int en=0; en<enemies.size(); en++)
	{		
		if (enemies[en].AbleToMove) enemies[en].inv.Move(-10,0);
		enemies[en].inv_newX = enemies[en].inv.GetPosition().x;
		enemies[en].inv_newY = enemies[en].inv.GetPosition().y;
		
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
	App.Clear();
	MyString end("Game is over!",MainCam.Center().x-80,MainCam.Center().y, sf::Color(255,69,0));
	//end.str.SetColor(sf::Color(255,69,0));
	App.Draw(end.str);
	App.Display();
	sleep(5);
}
