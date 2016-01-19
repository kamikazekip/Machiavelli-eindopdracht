#include "King.h"
#include "Game.h"

King::King( shared_ptr<Game> game ) :Role( game )
{
}


King::~King()
{
}

void King::PassiveAction()
{
	Role::PassiveAction();
	game->setNewKing(player);
	for (int i = 0; i < player->getBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Yellow)
		{
			player->addGold(1);
		}
	}
	
}
