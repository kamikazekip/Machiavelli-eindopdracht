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
	int index = -1;
	for (int i = 0; i < game->getRoles().size(); i++)
	{
		if (game->getRoles().at(i)->getPlayer() != this->player && game->getRoles().at(i)->getName() != "Moordenaar")
		{
			index++;
			ostringstream oss;
			oss << index;
			thiefConnections.insert(make_pair(oss.str(), game->getRoles().at(i)));
			*player << machiavelli::indent << "[" + oss.str() + "] " << game->getRoles().at(i)->getName() << machiavelli::rn;
		}
	}
	*player << machiavelli::endl;
}

void Thief::PlayerChoseOption(string chosenOption)
{
	map<string, shared_ptr<Role>>::iterator result = thiefConnections.find( chosenOption );
	if( result != thiefConnections.end() )
	{
		shared_ptr<Role> stolenRole = result->second;
		stolenRole->stolen = true;
		game->broadcast( player->get_name() + " ( de dief ) heeft de " + stolenRole->getName() + " bestolen!" + machiavelli::rn );
		game->handleCurrentRole();
	}
	else
	{
		*player << chosenOption << " was niet een van de opties! kies alstublieft opnieuw!" << machiavelli::rn;
		SpecialAction();
	}
	
}