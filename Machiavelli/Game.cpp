#include "Game.h"
#include <algorithm> 
#include <cstdlib>
#include <ctime>
Game::Game()
{
	gameState = GameState_PreGame;
	srand(time(NULL));
	buildingFactory = std::move(unique_ptr<BuildingFactory> { new BuildingFactory() });
	buildingStack = buildingFactory->getStartBuildings();
	//Shuffle the card deck
	std::random_shuffle(buildingStack.begin(), buildingStack.end());
	commands.insert( pair<string, game_function>( "inventory", &Game::look ) );
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
			else if ( gameState == GameState_Choosing_Role )
			{
				chooseOption( command );
			}
		}
		else
		{
			*player << "Sorry, " << player->get_name() << ", maar je bent niet aan de beurt!" << machiavelli::endl;
		}
	/*
	}
	else
	{
		*player << "Sorry, " << player->get_name() << ", we must wait until there are exactly 2 players in the game!" << machiavelli::endl;
	} 
	*/
}

void Game::chooseOption( ClientCommand command )
{
	map<string, pair<role_chosing_function, shared_ptr<Role>>>::iterator result = roleOptions.find( command.get_cmd() );

	if( result != roleOptions.end() )
	{
		( this->*( result->second.first ) )( result->second.second );
	}
}

void Game::addPlayer( shared_ptr<Player> player )
{
	string message = player->get_name() + " joined the game!";
	broadcast( message );

	/* Initialise the player */
	vector<shared_ptr<Building>> hand ( buildingStack.end() - 4, buildingStack.end() );
	buildingStack.erase( buildingStack.end() - 4, buildingStack.end() );
	player->addBuildings( hand );
	int newGold = 2;
	player->addGold( newGold );

	ostringstream oss;
	oss << newGold;

	/* Give the player info */
	*player << "Je hebt de volgende startgebouwen ontvangen:" << "\r\n";
	for( size_t c = 0; c < hand.size(); c++ )
		*player << "  " << hand.at( c )->getTextRepresentation() << "\r\n";
	*player << "Daarnaast heb je " << oss.str() << " goudstukken ontvangen!" << "\n" << machiavelli::endl;

	/* Wrap up */
	players.push_back( player );

	if( players.size() == 2 )
	{
		gameStart();
	}
}

void Game::removePlayer( shared_ptr<Player> player )
{
	players.erase( remove( players.begin(), players.end(), player ), players.end() );
}

void Game::broadcast( string message )
{
	for( size_t c = 0; c < players.size(); c++ )
	{
		*players.at( c ) << machiavelli::rn << message << machiavelli::rn;
	}
}

void Game::look( shared_ptr<Player> player  )
{
	std::cout << player->get_name() << std::endl;
}

void Game::gameStart()
{
	broadcast( "Het spel heeft nu 2 spelers, het spel begint! \r" );
	king = players[0];
	broadcast(king->get_name() + " heeft de koningskaart." + machiavelli::rn + king->get_name() + " zal starten door een rol te kiezen." + machiavelli::rn);
	chooseRoles();
}

void Game::chooseRoles()
{
	RoleFactory roleFactory;
	vector<shared_ptr<Role>> rolePool = roleFactory.getRoles();
	roles = roleFactory.getRoles();
	std::random_shuffle( rolePool.begin(), rolePool.end() );

	*king << "De " << rolePool[rolePool.size() - 1]->getName() << " is weg gelegd. " << machiavelli::rn << "Kies een van de volgende rollen:" + machiavelli::rn;
	rolePool.erase( rolePool.end()-1, rolePool.end() );
	
	gameState = GameState_Choosing_Role;

	for( size_t c = 0; c < rolePool.size(); c++ )
	{
		ostringstream oss;
		oss << c;
		*king << "  [" + oss.str() +"] " << rolePool.at( c )->getName() << machiavelli::rn;
		roleOptions.insert( std::make_pair( oss.str(), std::make_pair( &Game::pickRole, rolePool.at(c) ) ) );
	}
	*king << machiavelli::endl;
	turn = king;
}

void Game::pickRole( shared_ptr<Role> role )
{
	*turn << "Je bent nu de: " << role->getName() << ", je beurt is nu voorbij!" << machiavelli::endl;
}