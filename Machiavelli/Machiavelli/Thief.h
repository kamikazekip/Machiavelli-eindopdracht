#pragma once
#include "Role.h"

class Thief : public Role
{
public:
	Thief(shared_ptr<Game> game);
	~Thief();
	void SpecialAction();
};

