#include "Game.h"
#include <algorithm> 

Game::Game()
{
	buildingFactory = std::move(unique_ptr<BuildingFactory> { new BuildingFactory() });
	roleFactory = std::move(unique_ptr<RoleFactory> {new RoleFactory()});
	buildingStack = buildingFactory->getStartBuildings();
	rolePool = roleFactory->getRoles();
	roles = roleFactory->getRoles();
	commands.insert( pair<string, game_function>( "look", &Game::look ) );
}


Game::~Game()
{

}

void Game::handleCommand( ClientCommand command, shared_ptr<Player> player )
{
	/*
	if( players.size() == 2 )
	{
	*/
		if( turn == player )
		{
			map<string, game_function>::iterator result = commands.find( command.get_cmd() );

			if( result != commands.end() )
			{
				( this->*( result->second ) )( player );
			}
		}
		else
		{
			*player << "Sorry, " << player->get_name() << ", it is not your turn!" << machiavelli::endl;
		}
	/*
	}
	else
	{
		*player << "Sorry, " << player->get_name() << ", we must wait until there are exactly 2 players in the game!" << machiavelli::endl;
	} 
	*/
}

void Game::addPlayer( shared_ptr<Player> player )
{
	turn = player;
	string message = player->get_name() + " joined the game!";
	vector<shared_ptr<Building>> hand ( buildingStack.end() - 4, buildingStack.end() );
	buildingStack.erase( buildingStack.end() - 4, buildingStack.end() );
	player->addBuildings( hand );
	broadcast( message );
	*player << "You received the following cards:" << machiavelli::endl;
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
		*players.at( c ) << machiavelli::rn << message << machiavelli::endl;
	}
}

void Game::look( shared_ptr<Player> player  )
{
	std::cout << player->get_name() << std::endl;
}