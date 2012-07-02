#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <SFML/Graphics.hpp>

struct MyWindow
{
	MyWindow();
	void Run();
	void Create();
	
	sf::RenderWindow Window;
	sf::Event w_Event;
};



#endif
