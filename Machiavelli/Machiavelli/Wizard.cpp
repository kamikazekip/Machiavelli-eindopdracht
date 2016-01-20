#include "Wizard.h"
#include "Game.h"


Wizard::Wizard( shared_ptr<Game> game ) :Role( game )
{
}


Wizard::~Wizard()
{
}

void Wizard::SpecialAction()
{
	Role::SpecialAction();
	*player << "Met wie wil je je bouwkaarten wisselen? Of wil je je bouwkaarten inwisselen voor nieuwe?" << machiavelli::rn;
	int index = -1;
	for (int i = 0; i < game->getPlayers().size(); i++)
	{
		if (game->getPlayers().at(i) != this->player)
		{
			otherPlayerIndex = i;
			index++;
			ostringstream oss;
			oss << index;
			wizardConnections.insert(make_pair(oss.str(),&Wizard::tradeCardsWithPlayer));
			*player << machiavelli::indent << "[" + oss.str() + "] " << game->getPlayers().at(i)->get_name() << machiavelli::rn;
		}
	}
	index++;
	ostringstream oss;
	oss << index;
	wizardConnections.insert(make_pair(oss.str(), &Wizard::tradeCardsWithStack));
	*player << machiavelli::indent << "[" + oss.str() + "] " << "Ruil je kaarten met het dek" << machiavelli::rn;
	*player << machiavelli::endl;
}

void Wizard::tradeCardsWithPlayer()
{
	shared_ptr<Player> otherPlayer = game->getPlayers().at(otherPlayerIndex);
	vector<shared_ptr<Building>> myHand = player->getBuildings();
	vector<shared_ptr<Building>> otherHand = otherPlayer->getBuildings();
	player->clearHand();
	player->addBuildings(otherHand);
	otherPlayer->clearHand();
	otherPlayer->addBuildings(myHand);
	game->broadcast( player->get_name() + " heeft zijn bouwkaarten omgeruild met " + otherPlayer->get_name() + "!" + machiavelli::rn );
	game->handleCurrentRole();
}

void Wizard::tradeCardsWithStack()
{
	int amount = player->getBuildings().size();
	player->clearHand();
	player->addBuildings(game->getBuildingsFromStack(amount));
	game->broadcast( player->get_name() + " heeft zijn bouwkaarten omgeruild met het dek!" + machiavelli::rn );
	game->handleCurrentRole();
}

void Wizard::PlayerChoseOption(string chosenOption)
{
	map<string, wizard_function>::iterator result = wizardConnections.find( chosenOption );
	if( result != wizardConnections.end() )
	{
		wizard_function func = result->second;
		( this->*( func ) )( );
	}
	else
	{
		*player << chosenOption << " was niet een van de opties! kies alstublieft opnieuw!" << machiavelli::rn;
		SpecialAction();
	}
}