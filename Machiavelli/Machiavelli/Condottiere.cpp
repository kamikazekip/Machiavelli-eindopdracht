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

void Condottiere::SpecialAction()
{
	/*Role::SpecialAction();
	*player << "Welk gebouw wil je afbranden?" << machiavelli::rn;
	for (int i = 0; i < game->getPlayers().size(); i++)
	{
		if (game->getPlayers().at(i) != this->player)
		{
			ostringstream oss;
			oss << i;
			condottiereConnections.insert(make_pair(oss.str(), game->getRoles().at(i)));
			*player << machiavelli::indent << "[" + oss.str() + "] " << game->getRoles().at(i)->getName() << machiavelli::rn;
		}
	}
	*player << machiavelli::endl;*/
}

void Condottiere::PlayerChoseOption(string chosenOption)
{

}
