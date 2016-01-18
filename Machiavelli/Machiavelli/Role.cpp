#include "Role.h"

Role::Role()
{
	
}


Role::~Role()
{
}

void Role::Action()
{

}

void Role::setNameTurn(string name, int turn)
{
	this->name = name;
	this->turn = turn;
}

string Role::getName()
{
	return name;
}

void Role::setPlayer(shared_ptr<Player> player)
{
	this->player = player;
}
