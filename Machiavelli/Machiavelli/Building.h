#pragma once
#include <string>
#include <sstream>
enum Color { Yellow, Green, Blue, Red, Purple };

class Building
{
private:
	std::string name;
	Color color;
	int price;
	std::string colorString;
	std::string description;
	Color getColor(std::string color);
public:
	Building(  std::string name, int price, std::string color);
	~Building();	
	Color getColor();
	void setDescription( std::string description );
	std::string getTextRepresentation();
	std::string getName();
};

