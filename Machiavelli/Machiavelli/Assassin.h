#pragma once
#include "Role.h"
#include <map>
using namespace std;

class Assassin : public Role
{
public:
	Assassin(shared_ptr<Game> game);
	~Assassin();
	void SpecialAction();
	void PlayerChoseOption( string chosenOption );
private:
	map<string, shared_ptr<Role>> murderConnections;
};

