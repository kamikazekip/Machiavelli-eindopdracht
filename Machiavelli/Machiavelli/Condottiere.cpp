#include "Condottiere.h"
#include "Game.h"


Condottiere::Condottiere( shared_ptr<Game> game ) :Role( game )
{
}


Condottiere::~Condottiere()
{
}

void Condottiere::PassiveAction()
{
	Role::PassiveAction();
	for (int i = 0; i < player->getBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Red)
		{
			player->addGold(1);
		}
	}

}
