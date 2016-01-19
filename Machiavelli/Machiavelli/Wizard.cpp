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
	int index;
	for (int i = 0; i < game->getPlayers().size(); i++)
	{
		if (game->getPlayers().at(i) != this->player)
		{
			ostringstream oss;
			oss << i;
			wizardConnections.insert(make_pair(oss.str(),&Wizard::tradeCardsWithPlayer));
			*player << machiavelli::indent << "[" + oss.str() + "] " << game->getPlayers.at(i)->getName() << machiavelli::rn;
		}
		index = i;
	}
	ostringstream oss;
	oss << index;
	wizardConnections.insert(make_pair(oss.str(), &Wizard::tradeCardsWithStack));
	*player << machiavelli::indent << "[" + oss.str() + "] " << "Ruil je kaarten met het dek" << machiavelli::rn;
	*player << machiavelli::endl;
}

void Wizard::tradeCardsWithPlayer(string roleOption)
{
	int optionRole = stoi(roleOption);
	shared_ptr<Player> otherPlayer = game->getPlayers().at(optionRole);
	vector<shared_ptr<Building>> myHand = player->getBuildings();
	vector<shared_ptr<Building>> otherHand = otherPlayer->getBuildings();
	player->clearHand();
	player->addBuildings(otherHand);
	otherPlayer->clearHand();
	otherPlayer->addBuildings(myHand);
}

void Wizard::tradeCardsWithStack(string DEZESTRINGDOETNIKS)
{
	int amount = player->getBuildings().size();
	player->clearHand();
	player->addBuildings(game->getBuildingsFromStack(amount));
}

void Wizard::PlayerChoseOption(string chosenOption)
{
	wizard_function result = wizardConnections.at(chosenOption);
	(this->*(result))(chosenOption);
}