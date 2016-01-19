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
	Role::PassiveAction();
	for (int i = 0; i < player->getBuildings().size(); i++)
	{
		if (player->getBuildings().at(i)->getColor() == Red)
		{
			player->addGold(1);
		}
	}

}

void Condottiere::SpecialAction()
{
	Role::SpecialAction();
	*player << "Welk gebouw wil je afbranden?" << machiavelli::rn;
	for (int i = 0; i < game->getPlayers().size(); i++)
	{
		shared_ptr<Player> otherPlayer = game->getPlayers().at(i);
		if (otherPlayer != player)
		{
			for (int o = 0; o < otherPlayer->getTableBuildings().size(); o++)
			{
				if (otherPlayer->getTableBuildings().at(o)->getPrice() - 1 <= player->getGold())
				{
					ostringstream oss;
					oss << o;
					condottiereConnections.insert(make_pair(oss.str(), otherPlayer->getTableBuildings().at(o)));
					*player << machiavelli::indent << "[" + oss.str() + "] " << otherPlayer->getTableBuildings().at(o)->getTextRepresentation() << machiavelli::rn;
				}
			}			
		}
	}
	*player << machiavelli::endl;
}

void Condottiere::PlayerChoseOption(string chosenOption)
{
	shared_ptr<Building> destroyedBuilding = condottiereConnections.at(chosenOption);
	player->addGold((destroyedBuilding->getPrice() - 1)*-1);
	game->broadcast("De condotierre heeft het " + destroyedBuilding->getName() + " afgebrand!");
	for (int i = 0; i < game->getPlayers().size(); i++)
	{
		shared_ptr<Player> otherPlayer = game->getPlayers().at(i);
		otherPlayer->removeTableBuilding(destroyedBuilding);
	}
}
