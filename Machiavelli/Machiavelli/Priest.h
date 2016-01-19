#pragma once
#include "Role.h"

class Priest : public Role
{
public:
	Priest(shared_ptr<Game> game);
	~Priest();
	void PassiveAction();
};

