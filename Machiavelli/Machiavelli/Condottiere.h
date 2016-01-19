#pragma once
#include "Role.h"
#include <map>

class Condottiere : public Role
{
public:
	Condottiere(shared_ptr<Game> game);
	~Condottiere();
	void PassiveAction();
	void SpecialAction();
	void PlayerChoseOption(string chosenOption);
private:
	map<string, shared_ptr<Building>> condottiereConnections;
};

