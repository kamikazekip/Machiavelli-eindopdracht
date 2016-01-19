#pragma once
#include "Player.hpp"
#include <memory>
#include <string>

using namespace std;
class Game;

class Role
{
protected:
	shared_ptr<Player> player;
	string name;
	int turn;
	shared_ptr<Game> game;
	bool usedAction, usedStandardAction, usedPassive, usedBuildAction;
public:
	Role( shared_ptr<Game> game );
	~Role();
	virtual void Action();
	void setNameTurn(string name, int turn);
	virtual void ChooseGold();
	virtual void ChooseBuildingCards();
	virtual void PassiveAction();
	bool HasPlayer();
	shared_ptr<Player> getPlayer();
	string getName();
	void setPlayer(shared_ptr<Player> player);
	bool UsedAction();
	bool UsedStandardAction();
	bool UsedPassive();
	bool UsedBuildAction();
};

