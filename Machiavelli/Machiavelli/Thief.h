#pragma once
#include "Role.h"
#include <map>

class Thief : public Role
{
public:
	Thief(shared_ptr<Game> game);
	~Thief();
	void SpecialAction();
	void PlayerChoseOption(string chosenOption);
private:
	map<string, shared_ptr<Role>> thiefConnections;
};

