#pragma once
#include "Role.h"

class Assassin : public Role
{
public:
	Assassin(shared_ptr<Game> game);
	~Assassin();
	void SpecialAction();
	void PlayerChoseOption( string chosenOption );
};

