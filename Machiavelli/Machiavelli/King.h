#pragma once
#include "Role.h"

class King : public Role
{
public:
	King(shared_ptr<Game> game);
	~King();
};

