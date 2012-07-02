#include "mywindow.h"


MyWindow::MyWindow()
{
	Window.setVisible(false);
}

void MyWindow::Run()
{
	while(Window.isOpen())
	{
		while(Window.pollEvent(w_Event))
		{
			switch (w_Event.type)
			{
				case sf::Event::Closed:
					Window.close();
					break;
				default:
					break;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Window.close();
	}
		
}

void MyWindow::Create()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Insert))
	{
			Window.create(sf::VideoMode(400,300),"Menu");
			Window.setVisible(true);			
			this->Run();
	}
}

