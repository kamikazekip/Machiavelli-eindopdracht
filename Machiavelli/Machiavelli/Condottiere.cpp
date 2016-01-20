#include "Condottiere.h"
#include "Game.h"
#include "Player.hpp"

Condottiere::Condottiere( shared_ptr<Game> game ) :Role( game )
{
}


Condottiere::~Condottiere()
{
}

void Condottiere::PassiveAction()
{
	int counter = 0;
	Role::PassiveAction();
	for (int i = 0; i < player->getTableBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Red)
		{
			counter++;
			player->addGold(1);
		}
	}
	string counterStr = game->itos( counter );
	game->broadcast( player->get_name() + " ( de condottiere ) heeft " + counterStr + " goud ontvangen omdat hij " + counterStr + " rode gebouwen heeft gebouwd!" + machiavelli::rn );
}

void Condottiere::SpecialAction()
{
	int counter = 0;
	Role::SpecialAction();
	*player << "Welk gebouw wil je afbranden?" << machiavelli::rn;
	for (int i = 0; i < game->getPlayers().size(); i++)
	{
		shared_ptr<Player> otherPlayer = game->getPlayers().at(i);
		if (otherPlayer != player)
		{
			for (int o = 0; o < otherPlayer->getTableBuildings().size(); o++)
			{
				shared_ptr<Building> building = otherPlayer->getTableBuildings().at( o );
				int price = building->getPrice() - 1;

				if (price <= player->getGold() && !game->isPriest(otherPlayer))
				{
					counter++;
					ostringstream oss;
					oss << o;
					condottiereConnections.insert(make_pair(oss.str(), otherPlayer->getTableBuildings().at(o)));
					*player << machiavelli::indent << "[" + oss.str() + "] " << otherPlayer->getTableBuildings().at(o)->getTextRepresentation() << machiavelli::rn;
				}
			}			
		}
	}
	if( counter == 0 )
	{
		*player << "Sorry! er zijn geen gebouwen aanwezig die je kunt verbranden!" << machiavelli::rn;
		game->handleCurrentRole();
	}
	else
	{
		*player << machiavelli::endl;
	}
	
}

void Condottiere::PlayerChoseOption(string chosenOption)
{
	shared_ptr<Building> destroyedBuilding = condottiereConnections.at(chosenOption);
	player->addGold((destroyedBuilding->getPrice() - 1)*-1);
	game->broadcast("De condotierre heeft een " + destroyedBuilding->getName() + " afgebrand!" + machiavelli::rn);
	for (int i = 0; i < game->getPlayers().size(); i++)
	{
		shared_ptr<Player> otherPlayer = game->getPlayers().at(i);
		otherPlayer->removeTableBuilding(destroyedBuilding);
	}
	game->handleCurrentRole();
}
