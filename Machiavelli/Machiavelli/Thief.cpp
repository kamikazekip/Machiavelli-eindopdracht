#include "Thief.h"
#include "Game.h"


Thief::Thief( shared_ptr<Game> game ) :Role( game )
{
}


Thief::~Thief()
{
}

void Thief::SpecialAction()
{
	Role::SpecialAction();
	*player << "Van wie wil je het goud hebben?" << machiavelli::rn;
	for (int i = 0; i < game->getRoles().size(); i++)
	{
		if (game->getRoles().at(i)->getPlayer() != this->player)
		{
			ostringstream oss;
			oss << i;
			thiefConnections.insert(make_pair(oss.str(), game->getRoles().at(i)));
			*player << machiavelli::indent << "[" + oss.str() + "] " << game->getRoles().at(i)->getName() << machiavelli::rn;
		}
	}
	*player << machiavelli::endl;
}

void Thief::PlayerChoseOption(string chosenOption)
{
	thiefConnections.at(chosenOption)->stolen = true;
	game->broadcast( player->get_name() +  " ( de dief ) heeft de " + thiefConnections.at(chosenOption)->getName() + " bestolen!" + machiavelli::rn );
	game->handleCurrentRole();
}