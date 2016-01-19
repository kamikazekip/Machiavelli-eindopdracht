#include "Priest.h"
#include "Game.h"


Priest::Priest( shared_ptr<Game> game ) :Role( game )
{
}


Priest::~Priest()
{
}

void Priest::PassiveAction()
{
	Role::PassiveAction();
	for (int i = 0; i < player->getBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Yellow)
		{
			player->addGold(1);
		}
	}
}
