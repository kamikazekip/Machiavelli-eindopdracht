#pragma once
#include "Role.h"
#include <map>
using namespace std;

class Wizard;

typedef void ( Wizard::*wizard_function ) ();

class Wizard : public Role
{
public:
	Wizard(shared_ptr<Game> game);
	~Wizard();
	void SpecialAction();
	void PlayerChoseOption(string chosenOption);
private:
	map<string,wizard_function> wizardConnections;
	void tradeCardsWithPlayer();
	void tradeCardsWithStack();
	int otherPlayerIndex;
};

