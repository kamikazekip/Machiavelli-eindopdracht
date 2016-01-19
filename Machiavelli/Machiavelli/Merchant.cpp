#include "Merchant.h"
#include "Game.h"


Merchant::Merchant( shared_ptr<Game> game ) :Role( game )
{
}


Merchant::~Merchant()
{
}

void Merchant::PassiveAction()
{
	Role::PassiveAction();
	player->addGold(1);
	for (int i = 0; i < player->getBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Green)
		{
			player->addGold(1);
		}
	}
}
