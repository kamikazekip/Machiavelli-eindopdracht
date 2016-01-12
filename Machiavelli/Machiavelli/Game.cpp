#include "Game.h"
#include <algorithm> 


Game::Game()
{
	
}


Game::~Game()
{

}

void Game::handleCommand( ClientCommand command, shared_ptr<Socket> client, shared_ptr<Player> player )
{
	*client << player->get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
}

void Game::addPlayer( shared_ptr<Player> player )
{
	players.push_back( player );
}

void Game::removePlayer( shared_ptr<Player> player )
{
	players.erase( remove( players.begin(), players.end(), player ), players.end() );
}