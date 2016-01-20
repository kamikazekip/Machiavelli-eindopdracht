#include "Priest.h"
#include "Game.h"


Priest::Priest( shared_ptr<Game> game ) :Role( game )
{
	usedAction = true;
}


Priest::~Priest()
{

}

void Priest::PassiveAction()
{
	int counter = 0;
	Role::PassiveAction();
	for (int i = 0; i < player->getTableBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Blue)
		{
			counter++;
			player->addGold(1);
		}
		player->getTableBuildings().at(i)->canBeDestroyed = false;
	}

	string counterStr = game->itos( counter );
	game->broadcast( player->get_name() + " ( de prediker ) heeft " + counterStr + " goud ontvangen omdat hij " + counterStr + " blauwe gebouwen heeft gebouwd!" + machiavelli::rn);
}
