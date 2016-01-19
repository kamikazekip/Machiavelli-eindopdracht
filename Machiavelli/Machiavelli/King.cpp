#include "King.h"
#include "Game.h"

King::King( shared_ptr<Game> game ) :Role( game )
{
	usedAction = true;
}


King::~King()
{
}

void King::PassiveAction()
{
	int counter = 0;
	Role::PassiveAction();
	game->setNewKing(player);
	for (int i = 0; i < player->getTableBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Yellow)
		{
			counter++;
			player->addGold(1);
		}
	}
	string counterStr = game->itos( counter );
	game->broadcast( player->get_name() + " ( de koning ) heeft " + counterStr + " goud ontvangen omdat hij " + counterStr + " gele gebouwen heeft gebouwd!" );
}
