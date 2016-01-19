#include "Role.h"
#include "Game.h"

Role::Role( shared_ptr<Game> game )
{
	this->game = game;
	usedAction = false;
	usedStandardAction = false;
	usedPassive = false;
	usedBuildAction = false;
	murdered = false;
	stolen = false;
}

Role::~Role()
{
}

void Role::SpecialAction()
{
	game->setGameState( GameState_In_Role );
	usedAction = true;
}

void Role::setNameTurn(string name, int turn)
{
	this->name = name;
	this->turn = turn;
}

void Role::ChooseGold()
{
	usedStandardAction = true;
	player->addGold(2);
	game->broadcast( player->get_name() + " heeft 2 goudstukken gepakt!" + machiavelli::endl );
	game->handleCurrentRole();
}

void Role::ChooseBuildingCards()
{
	usedStandardAction = true;
	buildingOptions.clear();
	game->setGameState( GameState_In_Role_Choosing_Building );
	vector<shared_ptr<Building>> pickedFromDeck = game->getBuildingsFromStack( 2 );
	*player << "Welk gebouw wil je pakken? De andere wordt vernietigd!" << machiavelli::rn;
	for( size_t c = 0; c < pickedFromDeck.size(); c++ )
	{
		string counter = game->itos( c );
		buildingOptions.insert( make_pair( counter, pickedFromDeck.at( c ) ) );
		*player << machiavelli::indent << "[" + counter + "] " << pickedFromDeck.at( c )->getTextRepresentation() << machiavelli::rn;
	}
	*player << machiavelli::endl;
}

void Role::PassiveAction()
{
	usedPassive = true;
}

void Role::ChooseBuildingToBuild()
{
	buildingOptions.clear();
	game->setGameState( GameState_In_Role_Building );
	vector<shared_ptr<Building>> options = player->getBuildings();

	*player << "Welk gebouw wil je bouwen? Je hebt " << game->itos(player->getGold()) << " goud" << machiavelli::rn;
	*player << machiavelli::indent << "[0] bouwen annuleren" << machiavelli::rn;
	for( size_t c = 0; c < options.size(); c++ )
	{
		string counter = game->itos( c + 1 );
		buildingOptions.insert( make_pair( counter, options.at( c ) ) );
		*player << machiavelli::indent << "[" + counter + "] " << options.at( c )->getTextRepresentation() << machiavelli::rn;
	}
	*player << machiavelli::endl;
}

void Role::pickBuilding( string choice )
{
	map<string, shared_ptr<Building>>::iterator result = buildingOptions.find( choice );
	if( result != buildingOptions.end() )
	{
		shared_ptr<Building> chosenBuilding = result->second;
		player->addBuilding( chosenBuilding );
		usedStandardAction = true;
		*player << "Je hebt het volgende gebouw aan je hand toegevoegd: " << chosenBuilding->getTextRepresentation() << machiavelli::rn;
		game->handleCurrentRole();
	}
	else
	{
		*player << choice << " was niet een van de opties! kies alstublieft opnieuw!" << machiavelli::rn;
		ChooseBuildingCards();
	}
}

void Role::Build( string chosenOption )
{
	if( chosenOption == "0" )
		game->handleCurrentRole();
	else
	{
		map<string, shared_ptr<Building>>::iterator result = buildingOptions.find( chosenOption );
		if( result != buildingOptions.end() )
		{
			shared_ptr<Building> buildingToBuild = result->second;
			if( player->getGold() >= buildingToBuild->getPrice() )
			{
				player->addGold( buildingToBuild->getPrice() * -1 );
				player->buildBuilding( buildingToBuild );
				game->broadcast( player->get_name() + " heeft een " + buildingToBuild->getTextRepresentation() + " gebouwd en heeft nog " 
							   + game->itos(player->getGold()) + " goud over!" + machiavelli::rn );
				DoneBuilding();
			}
			else
			{
				*player << "Dit gebouw is te duur! Je hebt nog maar " << player->getGold() << " goud!" << machiavelli::rn;
				ChooseBuildingToBuild();
			}
		}
		else
		{
			*player << chosenOption << " was niet een van de opties! kies alstublieft opnieuw!" << machiavelli::rn;
			ChooseBuildingToBuild();
		}
	}
}

void Role::NextRole()
{
	usedAction = true;
	usedPassive = true;
	usedBuildAction = true;
	usedStandardAction = true;
	game->handleCurrentRole();
}

bool Role::HasPlayer()
{
	if (player)
	{
		return true;
	}
	return false;
}

shared_ptr<Player> Role::getPlayer()
{
	return player;
}

string Role::getName()
{
	return name;
}

void Role::setPlayer(shared_ptr<Player> player)
{
	this->player = player;
}

bool Role::UsedAction()
{	
	return usedAction;
}

bool Role::UsedStandardAction()
{
	return usedStandardAction;
}

bool Role::UsedPassive()
{
	return usedPassive;
}

bool Role::UsedBuildAction()
{
	return usedBuildAction;
}

void Role::PlayerChoseOption( string chosenOption )
{

}

void Role::DoneBuilding()
{
	usedBuildAction = true;
	game->handleCurrentRole();
}