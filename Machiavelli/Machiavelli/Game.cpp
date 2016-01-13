#include "Game.h"
#include <algorithm> 
#include <cstdlib>
#include <ctime>
Game::Game()
{
	srand(time(NULL));
	buildingFactory = std::move(unique_ptr<BuildingFactory> { new BuildingFactory() });
	roleFactory = std::move(unique_ptr<RoleFactory> {new RoleFactory()});
	buildingStack = buildingFactory->getStartBuildings();
	//Shuffle the card deck
	std::random_shuffle(buildingStack.begin(), buildingStack.end());
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
	broadcast( message );

	/* Initialise the player */
	vector<shared_ptr<Building>> hand ( buildingStack.end() - 4, buildingStack.end() );
	buildingStack.erase( buildingStack.end() - 4, buildingStack.end() );
	player->addBuildings( hand );
	int newGold = 2;
	player->addGold( newGold );

	std::ostringstream oss;
	oss << newGold;

	/* Give the player info */
	*player << "You received the following buildings:" << "\r\n";
	for( size_t c = 0; c < hand.size(); c++ )
		*player << "  " << hand.at( c )->getTextRepresentation() << "\r\n";
	*player << "You also received " << oss.str() << " pieces of gold!" << "\n" << machiavelli::endl;

	/* Wrap up */
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