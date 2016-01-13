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
	int turn;
public:
	Role();
	~Role();
	void virtual Action();
	void setNameTurn(string name, int turn);
};

