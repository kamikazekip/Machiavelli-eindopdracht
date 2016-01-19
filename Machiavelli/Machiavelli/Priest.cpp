#include "Priest.h"
#include "Game.h"


Priest::Priest( shared_ptr<Game> game ) :Role( game )
{
}


Priest::~Priest()
{
	for (int i = 0; i < player->getTableBuildings().size(); i++)
	{
		player->getTableBuildings().at(i)->canBeDestroyed = true;
	}
}

void Priest::PassiveAction()
{
	Role::PassiveAction();
	for (int i = 0; i < player->getBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Blue)
		{
			player->addGold(1);
		}
	}
	for (int i = 0; i < player->getTableBuildings().size(); i++)
	{
		player->getTableBuildings().at(i)->canBeDestroyed = false;
	}
}
