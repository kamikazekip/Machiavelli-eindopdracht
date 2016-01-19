#pragma once
#include "Role.h"
#include <map>
using namespace std;

class Wizard;

typedef void ( Wizard::*wizard_function ) (string option);

class Wizard : public Role
{
public:
	Wizard(shared_ptr<Game> game);
	~Wizard();
	void SpecialAction();
	void PlayerChoseOption(string chosenOption);
private:
	map<string,wizard_function> wizardConnections;
	void tradeCardsWithPlayer(string x);
	void tradeCardsWithStack(string x);
};

