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
	game->handleCurrentRole();
}

void Role::PassiveAction()
{
	usedPassive = true;
}

void Role::ChooseBuilding()
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
				ChooseBuilding();
			}
		}
		else
		{
			*player << chosenOption << " was niet een van de opties! kies alstublieft opnieuw!" << machiavelli::rn;
			ChooseBuilding();
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