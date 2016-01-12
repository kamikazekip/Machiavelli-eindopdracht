#include "Game.h"
#include <algorithm> 

Game::Game()
{
	commands.insert( pair<string, game_function>( "look", &Game::look ) );
}


Game::~Game()
{

}

void Game::handleCommand( ClientCommand command, shared_ptr<Player> player )
{
	if( players.size() == 2 )
	{
		if( turn == player )
		{
			map<string, game_function>::iterator result = commands.find( command.get_cmd() );

			if( result != commands.end() )
			{
				( this->*( result->second ) )( );
			}
		}
		else
		{
			*player->client << "Sorry, " << player->get_name() << ", it is not your turn!" << machiavelli::endl;
		}
	}
	else
	{
		*player->client << "Sorry, " << player->get_name() << ", we must wait until there are exactly 2 players in the game!" << machiavelli::endl;
	}
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

void Game::look(  )
{
	std::cout << "LOOK123456" << std::endl;
}