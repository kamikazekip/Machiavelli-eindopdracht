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

void Role::GetGold()
{
	player->addGold(2);
}

void Role::GetBuildingCards()
{

}

void Role::PassiveAction()
{

}

bool Role::HasPlayer()
{
	if (player)
	{
		return true;
	}
	return false;
}

shared_ptr<Player> Role::getPlayer()
{
	return player;
}

string Role::getName()
{
	return name;
}

void Role::setPlayer(shared_ptr<Player> player)
{
	this->player = player;
}
