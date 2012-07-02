#include "mystring.h"

sf::Font MyString::arial = arial.getDefaultFont();

MyString::MyString(std::string name, sf::Color color)
{
	str.setString(name);
	str.setFont(arial);
	str.setCharacterSize(20);
	str.setColor(color);
}

MyString::MyString(std::string name, double xCord, double yCord, sf::Color color)
{
	cords.x = xCord;
	cords.y = yCord;
	str.setString(name);
	str.setFont(MyString::arial);
	str.setCharacterSize(20);
	str.setPosition(cords);
	str.setColor(color);
}

MyString::MyString(const char* name, double startNum, sf::Color color)
{
	initNum=startNum;
	str.setString(name+UpdateString(0,true));
	str.setFont(MyString::arial);
	str.setCharacterSize(20);
	str.setColor(color);
}
MyString::MyString(const char* name, double startNum, double xCord, double yCord, sf::Color color)
{
	cords.x = xCord;
	cords.y = yCord;
	initNum=startNum;
	str.setString(name+UpdateString(0,true));
	str.setFont(MyString::arial);
	str.setCharacterSize(20);
	str.setPosition(cords);
	str.setColor(color);
}

std::string MyString::UpdateString(int value, bool operation)
{
	this->ss.str("");
	if (operation) this->initNum+=value;
	else this->initNum-=value;
	this->ss << this->initNum;
	return ss.str();
}

std::string MyString::UpdateString(std::stringstream& ss, float updater)
{
	ss.str("");
	ss << updater;
	return ss.str();
}
