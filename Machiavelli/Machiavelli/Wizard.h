#pragma once
#include "Role.h"

class Wizard : public Role
{
public:
	Wizard(shared_ptr<Game> game);
	~Wizard();
	void SpecialAction();
};

