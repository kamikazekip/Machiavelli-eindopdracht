#pragma once
#include "Role.h"

class Condottiere : public Role
{
public:
	Condottiere(shared_ptr<Game> game);
	~Condottiere();
};

