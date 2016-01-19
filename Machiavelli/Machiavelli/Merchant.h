#pragma once
#include "Role.h"

class Merchant : public Role
{
public:
	Merchant(shared_ptr<Game> game);
	~Merchant();
	void PassiveAction();
};

