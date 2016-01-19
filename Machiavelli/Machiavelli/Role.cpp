#include "Role.h"
#include "Game.h"

Role::Role( shared_ptr<Game> game )
{
	this->game = game;
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

shared_ptr<Player> Role::getPlayer()
{
	return player;
}
