#pragma once
#include <string>
enum Color { Yellow, Green, Blue, Red, Purple };

class Building
{
private:
	std::string name;
	Color color;
	int price;
	std::string colorString;
	std::string description;
public:
	Building(  std::string name, int price, std::string color);
	~Building();
	Color getColor( std::string color );
	void setDescription( std::string description );
};

