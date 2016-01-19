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
	virtual void Action();
	void setNameTurn(string name, int turn);
	virtual void GetGold();
	virtual void GetBuildingCards();
	virtual void PassiveAction();
	bool HasPlayer();
	string getName();
	void setPlayer(shared_ptr<Player> player);
};

