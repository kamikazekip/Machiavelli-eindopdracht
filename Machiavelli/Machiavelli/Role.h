#pragma once
#include "Player.hpp"
#include <memory>
#include <string>

using namespace std;

class Role
{
private:
	shared_ptr<Player> player;
	string name;
public:
	Role();
	~Role();
	void virtual Action();
};

