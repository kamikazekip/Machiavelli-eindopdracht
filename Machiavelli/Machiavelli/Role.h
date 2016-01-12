#pragma once
#include "Player.hpp"
#include <memory>

using namespace std;

class Role
{
private:
	shared_ptr<Player> player;
public:
	Role();
	~Role();
	void Action();
};

