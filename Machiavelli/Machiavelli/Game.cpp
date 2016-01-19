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
	commands.insert( pair<string, game_function>( "cheat", &Game::cheat ) );
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
				( this->*( result->second ) )( player );
			else if ( gameState != GameState_PreGame )
				chooseOption( command );
		}
		else
		{
			*player << "Sorry, " << player->get_name() << ", maar je bent niet aan de beurt!" << machiavelli::endl;
		}
	}
	else
	{
		*player << "Sorry, " << player->get_name() << ", we must wait until there are exactly 2 players in the game!" << machiavelli::endl;
	} 
}

void Game::chooseOption( ClientCommand command )
{
	if( gameState == GameState_Choosing_Role || gameState == GameState_Removing_Role )
	{
		map<string, pair<role_chosing_function, shared_ptr<Role>>>::iterator result = roleOptions.find( command.get_cmd() );

		if( result != roleOptions.end() )
		{
			( this->*( result->second.first ) )( result->second.second );
		}
	}
	if( gameState == GameState_In_Game )
	{
		map<string, role_function>::iterator result = roleFunctions.find( command.get_cmd() );
		if( result != roleFunctions.end() )
		{
			role_function func = result->second;
			( (*currentRole).*( func ) )( );
		}
	}
	if( gameState == GameState_In_Role )
	{
		currentRole->PlayerChoseOption( command.get_cmd() );
	}
}

void Game::addPlayer( shared_ptr<Player> player )
{
	string message = player->get_name() + " joined the game!";
	broadcast( message );

	/* Initialise the player */
	vector<shared_ptr<Building>> hand = getBuildingsFromStack( 4 );
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
		*players.at( c ) << machiavelli::rn << message;
	}
}

void Game::look( shared_ptr<Player> player  )
{
	std::cout << player->get_name() << std::endl;
}

void Game::gameStart()
{
	broadcast( machiavelli::rn + "Het spel heeft nu 2 spelers, het spel begint! \r" );
	king = players[0];
	otherPlayer = players[1];
	broadcast(king->get_name() + " heeft de koningskaart." + machiavelli::rn + king->get_name() + " zal starten door een rol te kiezen." + machiavelli::rn + machiavelli::endl);
	chooseRoles();
}

void Game::chooseRoles()
{
	shared_ptr<Game> gamePointer { this };
	std::shared_ptr<RoleFactory> roleFactory = std::make_shared<RoleFactory>( gamePointer );
	rolePool = roleFactory->getRoles();
	roles = roleFactory->getRoles();
	std::random_shuffle( rolePool.begin(), rolePool.end() );

	*king << "De " << rolePool[rolePool.size() - 1]->getName() << " is weg gelegd. " << machiavelli::rn;
	rolePool.erase( rolePool.end()-1, rolePool.end() );

	sequence.push_back( make_pair( &Game::pickRole,		king ) );
	sequence.push_back( make_pair( &Game::removeRole,	otherPlayer ) );
	sequence.push_back( make_pair( &Game::pickRole,		otherPlayer ) );
	sequence.push_back( make_pair( &Game::removeRole,	king ) );
	sequence.push_back( make_pair( &Game::pickRole,		king ) );
	sequence.push_back( make_pair( &Game::removeRole,	otherPlayer ) );
	sequence.push_back( make_pair( &Game::pickRole,		otherPlayer ) );

	nextSegment();
}

void Game::pickedRole(shared_ptr<Role> choice )
{
	choice->setPlayer(turn);
	*turn << "Je bent nu de: " << choice->getName() << ", je beurt is nu voorbij!" << machiavelli::endl;
	rolePool.erase(std::remove(rolePool.begin(), rolePool.end(), choice), rolePool.end());
	nextSegment();
}

void Game::removedRole(shared_ptr<Role> choice)
{
	*turn << "Je hebt nu de: " << choice->getName() << " weg gelegd!" << machiavelli::endl;
	rolePool.erase(std::remove(rolePool.begin(), rolePool.end(), choice), rolePool.end());
	nextSegment();
}

void Game::pickRole( shared_ptr<Player> player)
{
	roleOptions.clear();
	turn = player;
	*turn << "Kies een van de volgende rollen om zelf te zijn:" + machiavelli::rn;
	gameState = GameState_Choosing_Role;
	for (size_t c = 0; c < rolePool.size(); c++)
	{
		ostringstream oss;
		oss << c;
		*turn << machiavelli::indent << "[" + oss.str() + "] " << rolePool.at(c)->getName() << machiavelli::rn;
		roleOptions.insert(std::make_pair(oss.str(), std::make_pair(&Game::pickedRole, rolePool.at(c))));
	}
	*turn << machiavelli::endl;
}

void Game::removeRole( shared_ptr<Player> player )
{
	roleOptions.clear();
	turn = player;
	*turn << "Kies een van de volgende rollen om weg te leggen:" + machiavelli::rn;
	gameState = GameState_Removing_Role;
	for (size_t c = 0; c < rolePool.size(); c++)
	{
		ostringstream oss;
		oss << c;
		*turn << machiavelli::indent <<"[" + oss.str() + "] " << rolePool.at(c)->getName() << machiavelli::rn;
		roleOptions.insert(std::make_pair(oss.str(), std::make_pair(&Game::removedRole, rolePool.at(c))));
	}
	*turn << machiavelli::endl;
}

void Game::nextSegment() {
	if (sequence.size() < 1)
	{
		startPlayRound();
		return;
	}
	pair<sequence_function, shared_ptr<Player>> segment = sequence[0];
	sequence.erase(sequence.begin(), sequence.begin() + 1);
	sequence_function function = segment.first;
	shared_ptr<Player> player = segment.second;
	(this->*(function))(player);
}

void Game::startPlayRound()
{
	turn = roles.at(0)->getPlayer();
	currentRole = roles.at(0);
	broadcast( "De " + currentRole->getName() + " is nu aan de beurt!" + machiavelli::endl );
	handleRole( currentRole );
}

void Game::handleRole( shared_ptr<Role> role )
{
	gameState = GameState_In_Game;
	if( !role->HasPlayer() )
	{
		broadcast( "De " + role->getName() + " is niet gekozen deze ronde!" + machiavelli::rn );
		nextRole();
	}
	else
	{
		if( role->UsedPassive() )
			role->PassiveAction();
		if( role->UsedAction() && role->UsedStandardAction() )
		{
			broadcast( "De beurt van de " + role->getName() + " is voorbij!" + machiavelli::rn );
			nextRole();
		}
		else
		{
			*role->getPlayer() << "Kies een van de volgende acties!" << machiavelli::rn;
			*role->getPlayer() << machiavelli::indent << "[look] Bekijk het goud en gebouwen van de tegenstander" << machiavelli::rn;
			string counter = "0";
			if( !role->UsedStandardAction() )
			{
				roleFunctions.insert( std::make_pair( counter, &Role::ChooseGold ) );
				*role->getPlayer() << machiavelli::indent << "[" + counter + "] Neem 2 goudstukken" << machiavelli::rn;
				int counterInt = stoi( counter );
				counterInt++;
				ostringstream oss;
				oss << counterInt;
				counter = oss.str();
				roleFunctions.insert( std::make_pair( counter, &Role::ChooseBuildingCards ) );
				*role->getPlayer() << machiavelli::indent << "[" + counter + "] Neem 2 bouwkaarten en leg er 1 af" << machiavelli::rn;
			}
			if( !role->UsedAction() )
			{
				int counterInt = stoi( counter );
				counterInt++;
				ostringstream oss;
				oss << counterInt;
				counter = oss.str();;
				roleFunctions.insert( std::make_pair( counter, &Role::SpecialAction ) );
				*role->getPlayer() << machiavelli::indent << "[" + counter + "] Maak gebruik van de karaktereigenschap van de " << role->getName() << machiavelli::rn;
			}
			*role->getPlayer() << machiavelli::endl;
		}
	}	
}

void Game::nextRole()
{

}

void Game::cheat( shared_ptr<Player> player )
{
	roles[0]->setPlayer( king );
	roles[1]->setPlayer( king );
	roles[2]->setPlayer( otherPlayer );
	roles[3]->setPlayer( otherPlayer );
	string message = "Cheat geactiveerd! " + king->get_name() + " is de " + roles[0]->getName() + " en de " + roles[1]->getName() + "!" + machiavelli::rn
		+ otherPlayer->get_name() + " is de " + roles[2]->getName() + " en de " + roles[3]->getName() + "!";
	broadcast(message);
	broadcast( "Het spel begint nu!" + machiavelli::rn + machiavelli::endl  );
	startPlayRound();
}

void Game::setNewKing( shared_ptr<Player> newKing )
{

}

vector<shared_ptr<Building>> Game::getBuildingsFromStack( int amount )
{
	vector<shared_ptr<Building>> buildings ( buildingStack.end() - 2, buildingStack.end() );
	buildingStack.erase( buildingStack.end() - 4, buildingStack.end() );
	return buildings;
}

void Game::setGameState( GameState newState )
{
	gameState = newState;
}

vector<shared_ptr<Role>> Game::getRoles()
{
	return roles;
}
