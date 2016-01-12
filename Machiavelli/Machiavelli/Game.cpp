#include "Game.h"
#include <algorithm> 


Game::Game()
{
	
}


Game::~Game()
{

}

void Game::handleCommand( ClientCommand command, shared_ptr<Player> player )
{
	if( turn == player )
	{
		*player->client << "Ja je bent aan de beurt!" << machiavelli::endl;
	}
	else
	{
		*player->client << "Sorry, " << player->get_name() << ", it is not your turn!" << machiavelli::endl;
	}
	//*client << player->get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now." << machiavelli::rn << machiavelli::prompt;
}

void Game::addPlayer( shared_ptr<Player> player )
{
	turn = player;
	std::string message = player->get_name() + " joined the game!";
	broadcast( message );
	players.push_back( player );
}

void Game::removePlayer( shared_ptr<Player> player )
{
	players.erase( remove( players.begin(), players.end(), player ), players.end() );
}

void Game::broadcast( string message )
{
	for( size_t c = 0; c < players.size(); c++ )
	{
		*players.at( c )->client << machiavelli::rn << message << machiavelli::endl;
	}
}