#include "mystring.h"

sf::Font MyString::arial = arial.GetDefaultFont();

MyString::MyString(std::string name, sf::Color color)
{
	str.SetText(name);
	str.SetFont(arial);
	str.SetSize(20);
	str.SetColor(color);
}

MyString::MyString(std::string name, double xCord, double yCord, sf::Color color)
{
	cords.x = xCord;
	cords.y = yCord;
	str.SetText(name);
	str.SetFont(MyString::arial);
	str.SetSize(20);
	str.SetPosition(cords);
	str.SetColor(color);
}

MyString::MyString(const char* name, double startNum, sf::Color color)
{
	initNum=startNum;
	str.SetText(name+UpdateString(0,true));
	str.SetFont(MyString::arial);
	str.SetSize(20);
	str.SetColor(color);
}
MyString::MyString(const char* name, double startNum, double xCord, double yCord, sf::Color color)
{
	cords.x = xCord;
	cords.y = yCord;
	initNum=startNum;
	str.SetText(name+UpdateString(0,true));
	str.SetFont(MyString::arial);
	str.SetSize(20);
	str.SetPosition(cords);
	str.SetColor(color);
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
