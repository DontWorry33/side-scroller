#ifndef MYSTRING_H
#define MYSTRING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

struct MyString
{
	MyString(std::string name, sf::Color color);
	MyString(std::string name, double xCord, double yCord, sf::Color color);
	
	MyString(const char* name, double startNum, sf::Color color);
	MyString(const char* name, double startNum, double xCord, double yCord, sf::Color color);
	
	static sf::Font arial;
	
	std::string UpdateString(int value, bool operation);
	std::string UpdateString(std::stringstream& ss, float updater);

	sf::Text str;
	std::stringstream ss;
	double initNum;
	sf::Vector2f cords;
	
};

#endif
