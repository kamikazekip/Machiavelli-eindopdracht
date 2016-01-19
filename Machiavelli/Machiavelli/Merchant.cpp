#include "Merchant.h"
#include "Game.h"


Merchant::Merchant( shared_ptr<Game> game ) :Role( game )
{
	this->usedAction = true;
}


Merchant::~Merchant()
{
}

void Merchant::PassiveAction()
{
	int counter = 0;
	Role::PassiveAction();
	player->addGold(1);
	for (int i = 0; i < player->getTableBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Green)
		{
			counter++;
			player->addGold(1);
		}
	}
	string counterStr = game->itos( counter );
	game->broadcast( player->get_name() + " ( de koopman ) heeft 1 extra goudstuk ontvangen omdat hij de koopman is!" );
	game->broadcast( player->get_name() + " ( de koopman ) heeft " + counterStr + " goud ontvangen omdat hij " + counterStr + " groene gebouwen heeft gebouwd!" );
}
