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
	for (int i = 0; i < game->getRoles().size(); i++)
	{
		if (game->getRoles().at(i)->getPlayer() != this->player)
		{
			ostringstream oss;
			oss << i;
			wizardConnections.insert(make_pair(oss.str(),&Wizard::tradeCardsWithPlayer));
			*player << machiavelli::indent << "[" + oss.str() + "] " << game->getRoles().at(i)->getName() << machiavelli::rn;
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
	shared_ptr<Role> role = game->getRoles().at(optionRole);
	vector<shared_ptr<Building>> myHand = player->getBuildings();
	vector<shared_ptr<Building>> otherHand = role->getPlayer()->getBuildings();
	player->clearHand();
	player->addBuildings(otherHand);
	role->getPlayer()->clearHand();
	role->getPlayer()->addBuildings(myHand);
}

void Wizard::tradeCardsWithStack(string DEZESTRINGDOETNIKS)
{
	int amount = player->getBuildings().size();
	player->clearHand();
	player->addBuildings(game->getBuildingsFromStack(amount));
}

void Wizard::PlayerChoseOption(string chosenOption)
{
	//*player << "Je hebt de " << wizardConnections.at(chosenOption)->getName() << " gekozen!" << machiavelli::endl;
	// ZET DIE ENE BOOLEAN
}