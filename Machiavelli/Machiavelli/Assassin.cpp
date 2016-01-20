#include "Assassin.h"
#include "Game.h"


Assassin::Assassin( shared_ptr<Game> game ) :Role( game )
{
}


Assassin::~Assassin()
{
}

void Assassin::SpecialAction()
{
	Role::SpecialAction();
	*player << "Wie zou je graag willen vermoorden?" << machiavelli::rn;
	for( int i = 0; i < game->getRoles().size(); i++ )
	{
		if( game->getRoles().at( i )->getPlayer() != this->player )
		{
			ostringstream oss;
			oss << i;
			murderConnections.insert( make_pair( oss.str(), game->getRoles().at( i ) ) );
			*player << machiavelli::indent << "[" + oss.str() + "] " << game->getRoles().at( i )->getName() << machiavelli::rn;
		}
	}
	*player << machiavelli::endl;
}

void Assassin::PlayerChoseOption( string chosenOption )
{
	map<string, shared_ptr<Role>>::iterator result = murderConnections.find( chosenOption );
	if( result != murderConnections.end() )
	{
		shared_ptr<Role> roleToAssasinate = result->second;
		roleToAssasinate->murdered = true;
		game->broadcast( player->get_name() + " ( de moordenaar ) heeft de " + roleToAssasinate->getName() + " vermoord!" + machiavelli::rn );
		game->handleCurrentRole();
	}
	else
	{
		*player << chosenOption << " was niet een van de opties! kies alstublieft opnieuw!" << machiavelli::rn;
		SpecialAction();
	}
}