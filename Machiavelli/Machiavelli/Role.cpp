#include "Role.h"
#include "Game.h"

Role::Role( shared_ptr<Game> game )
{
	this->game = game;
	usedAction = false;
	usedStandardAction = false;
}


Role::~Role()
{
}

void Role::SpecialAction()
{
	usedAction = true;
}

void Role::setNameTurn(string name, int turn)
{
	this->name = name;
	this->turn = turn;
}

void Role::ChooseGold()
{
	usedStandardAction = true;
	player->addGold(2);
}

void Role::ChooseBuildingCards()
{
	usedStandardAction = true;
}

void Role::PassiveAction()
{
	usedPassive = true;
}

void Role::Build()
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

bool Role::UsedAction()
{	
	return usedAction;
}

bool Role::UsedStandardAction()
{
	return usedStandardAction;
}

bool Role::UsedPassive()
{
	return usedPassive;
}

bool Role::UsedBuildAction()
{
	return usedBuildAction;
}

void Role::PlayerChoseOption( string chosenOption )
{

}