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
	game->setGameState( GameState_In_Role_Building );
	vector<shared_ptr<Building>> options = player->getBuildings();

	*player << "Welk gebouw wil je bouwen?" << machiavelli::rn;
	for( size_t c = 0; c < options.size(); c++ )
	{
		string counter = game->itos( c );
		buildingOptions.insert( make_pair( counter, options.at( c ) ) );
		*player << machiavelli::indent << "[" + counter + "] " << options.at( c )->getTextRepresentation() << machiavelli::rn;
	}
	*player << machiavelli::endl;
}

void Role::Build( string chosenOption )
{
	*player << "you chose " << chosenOption << machiavelli::endl;
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