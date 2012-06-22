#include "mycamera.h"

MyCamera::MyCamera(sf::Vector2f attr, int startspeed)
{
	init_Center.x = attr.x/2;
	init_Center.y = attr.y/2;
	init_HalfSize.x = attr.x/2;
	init_HalfSize.y = attr.y/2;
	MainView.SetCenter(init_Center);
	MainView.SetHalfSize(init_HalfSize);
	speed=startspeed;
}

void MyCamera::MoveCamera(sf::RenderWindow& App)
{
	MainView.Move(speed,0);
	SpeedUp(1500,2);
	SpeedUp(2500,4);
	SpeedUp(4000,6);
	SpeedUp(8000,8);
	App.SetView(MainView);
}

sf::Vector2f MyCamera::Center()
{
	sf::Vector2f tmp = MainView.GetCenter();
	return tmp;
}

void MyCamera::SpeedUp(unsigned int xRange, unsigned int spd)
{
	if (this->Center().x >= xRange) 
	{
		speed=spd;
	}
}
