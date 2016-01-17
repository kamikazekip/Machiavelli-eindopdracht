#include "Building.h"



Building::Building( std::string name, int price, std::string color )
{
	this->color = getColor( color );
	this->price = price;
	this->name = name;
	colorString = color;
}


Building::~Building()
{
}

Color Building::getColor( std::string color )
{
	if( color == "geel" )
		return Yellow;
	else if( color == "groen" )
		return Green;
	else if( color == "blauw" )
		return Blue;
	else if( color == "rood" )
		return Red;
	else if( color == "lila" )
		return Purple;
	else
		return Yellow;
}

void Building::setDescription( std::string description )
{
	this->description = description;
}

std::string Building::getTextRepresentation()
{
	std::ostringstream oss;
	oss << price;;
	std::string text = name + " (" + colorString + ", " + oss.str() + "):";
	return text;
}
