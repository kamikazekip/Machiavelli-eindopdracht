#include "Game.h"
#include <algorithm> 
#include <cstdlib>
#include <ctime>
Game::Game()
{
	gameState = GameState_PreGame;
	srand(time(NULL));
	buildingFactory = move(unique_ptr<BuildingFactory> { new BuildingFactory() });
	buildingStack = buildingFactory->getStartBuildings();
	//Shuffle the card deck
	random_shuffle(buildingStack.begin(), buildingStack.end());
	commands.insert( pair<string, game_function>( "bekijken", &Game::look ) );
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
		*player << "Sorry, " << player->get_name() << ", maar we moeten wachten totdat er exact 2 spelers in het spel zijn!" << machiavelli::endl;
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
	else if( gameState == GameState_In_Game )
	{
		map<string, role_function>::iterator result = roleFunctions.find( command.get_cmd() );
		if( result != roleFunctions.end() )
		{
			role_function func = result->second;
			( (*currentRole).*( func ) )( );
		}
		else
		{
			*turn << command.get_cmd() << " is niet een van de opties!" << machiavelli::rn << machiavelli::rn;
			handleCurrentRole();
		}
	}
	else if( gameState == GameState_In_Role )
	{
		currentRole->PlayerChoseOption( command.get_cmd() );
	}
	else if( gameState == GameState_In_Role_Building )
	{
		currentRole->Build( command.get_cmd() );
	}
}

void Game::addPlayer( shared_ptr<Player> player )
{
	string message = player->get_name() + " joined the game!";
	broadcast( message );

	/* Initialise the player */
	vector<shared_ptr<Building>> hand = getBuildingsFromStack( 4 );
	player->addBuildings( hand );
	int newGold = 2000;
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
	for (int i = 0; i < players.size(); i++)
	{
		shared_ptr<Player> tempPlayer = players.at(i);
		*player << tempPlayer->get_name() << " heeft " << itos(tempPlayer->getGold()) << " goud, en de volgende gebouwen:" << machiavelli::rn;
		for (int o = 0; o < tempPlayer->getTableBuildings().size(); o++)
		{
			*player << machiavelli::indent << tempPlayer->getTableBuildings().at(o)->getTextRepresentation() << machiavelli::rn;
		}
	}
	*player << machiavelli::rn;

	*player << "Je hebt de volgende hand:" << machiavelli::rn;
	for( int c = 0; c < player->getBuildings().size(); c++ )
	{
		*player << machiavelli::indent << player->getBuildings().at( c )->getTextRepresentation() << machiavelli::rn;
	}
	handleCurrentRole();
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
	shared_ptr<RoleFactory> roleFactory = make_shared<RoleFactory>( gamePointer );
	rolePool = roleFactory->getRoles();
	roles = roleFactory->getRoles();
	random_shuffle( rolePool.begin(), rolePool.end() );

	*king << "De " << rolePool[rolePool.size() - 1]->getName() << " is weg gelegd. " << machiavelli::rn;
	rolePool.erase( rolePool.end()-1, rolePool.end() );

	sequence.clear();

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
	rolePool.erase(remove(rolePool.begin(), rolePool.end(), choice), rolePool.end());
	nextSegment();
}

void Game::removedRole(shared_ptr<Role> choice)
{
	*turn << "Je hebt nu de: " << choice->getName() << " weg gelegd!" << machiavelli::endl;
	rolePool.erase(remove(rolePool.begin(), rolePool.end(), choice), rolePool.end());
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
		roleOptions.insert(make_pair(oss.str(), make_pair(&Game::pickedRole, rolePool.at(c))));
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
		roleOptions.insert( make_pair(oss.str(), make_pair(&Game::removedRole, rolePool.at(c))));
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

	if( !currentRole->HasPlayer() )
	{
		broadcast( "De " + currentRole->getName() + " is niet gekozen deze ronde!" + machiavelli::rn );
		nextRole();
	}
		
	broadcast( "De " + currentRole->getName() + " is nu aan de beurt!" + machiavelli::endl );
	handleCurrentRole( );
}

void Game::handleCurrentRole( )
{
	gameState = GameState_In_Game;
	if( !currentRole->UsedPassive() )
		currentRole->PassiveAction();
	if( currentRole->UsedAction() && currentRole->UsedStandardAction() && currentRole->UsedBuildAction() )
	{
		broadcast( "De beurt van de " + currentRole->getName() + " is voorbij!" + machiavelli::rn );
		nextRole();
	}
	else
	{
		roleFunctions.clear();
		*currentRole->getPlayer() << "Kies een van de volgende acties!" << machiavelli::rn;
		*currentRole->getPlayer() << machiavelli::indent << "[bekijken] Bekijk het goud en gebouwen van de tegenstander" << machiavelli::rn;
		string counter = "-1";
		if( !currentRole->UsedStandardAction() )
		{
			counter = itos( stoi( counter ) + 1 );
			roleFunctions.insert( make_pair( counter, &Role::ChooseGold ) );
			*currentRole->getPlayer() << machiavelli::indent << "[" + counter + "] Neem 2 goudstukken" << machiavelli::rn;
			counter = itos( stoi( counter ) + 1 );
			roleFunctions.insert( make_pair( counter, &Role::ChooseBuildingCards ) );
			*currentRole->getPlayer() << machiavelli::indent << "[" + counter + "] Neem 2 bouwkaarten en leg er 1 af" << machiavelli::rn;
		}
		else if( !currentRole->UsedBuildAction() )
		{
			counter = itos( stoi( counter ) + 1 );
			roleFunctions.insert( make_pair( counter, &Role::ChooseBuilding ) );
			*currentRole->getPlayer() << machiavelli::indent << "[" + counter + "] Bouw een gebouw" << machiavelli::rn;
		}
		if( !currentRole->UsedAction() )
		{
			counter = itos( stoi( counter ) + 1 );
			roleFunctions.insert( make_pair( counter, &Role::SpecialAction ) );
			*currentRole->getPlayer() << machiavelli::indent << "[" + counter + "] Maak gebruik van de karaktereigenschap van de " << currentRole->getName() << machiavelli::rn;
		}
		if( currentRole->UsedStandardAction() && currentRole->UsedAction() )
		{
			counter = itos( stoi( counter ) + 1 );
			roleFunctions.insert( make_pair( counter, &Role::NextRole ) );
			*currentRole->getPlayer() << machiavelli::indent << "[" + counter + "] beurt beëindigen" << machiavelli::rn;
		}

		*currentRole->getPlayer() << machiavelli::endl;
	}	
}

void Game::nextRole()
{
	/* Get the next role */
	vector<shared_ptr<Role>>::iterator roleIt = next( find( roles.begin(), roles.end(), currentRole ), 1 );

	/* If we are not at the end */
	if( roleIt != roles.end() )
	{
		currentRole = *roleIt;
		turn = currentRole->getPlayer();
		broadcast( "De " + currentRole->getName() + " is nu aan de beurt!" + machiavelli::rn);
		if( currentRole->HasPlayer() )
		{
			string playerName = currentRole->getPlayer()->get_name();
			broadcast( playerName + " is de " + currentRole->getName() + "! " + playerName + " is nu dus aan de beurt!" + machiavelli::rn);
		}
		if( !currentRole->HasPlayer() )
		{
			broadcast( "De " + currentRole->getName() + " is niet gekozen deze ronde!" + machiavelli::rn );
			nextRole();
		}
		else if( currentRole->murdered )
		{
			broadcast( "De " + currentRole->getName() + " is vermoord en kan dus niets doen deze ronde!" + machiavelli::rn );
			nextRole();
		}
		else if( currentRole->stolen )
		{
			broadcast("De " + currentRole->getName() + " is bestolen verliest nu zijn goud!" + machiavelli::rn);
			int gold = currentRole->getPlayer()->getGold();
			roles[1]->getPlayer()->addGold(gold);
			currentRole->getPlayer()->addGold(gold*-1);
			handleCurrentRole();
		}
		else
			handleCurrentRole();
	}
	else
		broadcast( "Speelronde voorbij!" + machiavelli::endl );
}

void Game::cheat( shared_ptr<Player> player )
{
	roles[5]->setPlayer( king );
	roles[7]->setPlayer( king );
	roles[3]->setPlayer( otherPlayer );
	roles[4]->setPlayer( otherPlayer );
	string message = "Cheat geactiveerd! " + king->get_name() + " is de " + roles[5]->getName() + " en de " + roles[7]->getName() + "!" + machiavelli::rn
		+ otherPlayer->get_name() + " is de " + roles[3]->getName() + " en de " + roles[4]->getName() + "!";
	broadcast(message);
	broadcast( "Het spel begint nu!" + machiavelli::rn + machiavelli::endl  );
	startPlayRound();
}

void Game::setNewKing( shared_ptr<Player> newKing )
{
	king = newKing; // :'D
}

vector<shared_ptr<Building>> Game::getBuildingsFromStack( int amount )
{
	vector<shared_ptr<Building>> buildings ( buildingStack.end() - amount, buildingStack.end() );
	buildingStack.erase( buildingStack.end() - amount, buildingStack.end() );
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

string Game::itos( int i )
{
	ostringstream oss;
	oss << i;
	return oss.str();
}

vector<shared_ptr<Player>> Game::getPlayers()
{
	return players;
}