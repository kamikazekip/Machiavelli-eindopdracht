#pragma once
#include "Player.hpp"
#include <memory>
#include <string>
#include <map>

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
	map<string, shared_ptr<Building>> buildingOptions;
public:
	Role( shared_ptr<Game> game );
	~Role();
	virtual void SpecialAction();
	void setNameTurn(string name, int turn);
	virtual void ChooseGold();
	virtual void ChooseBuildingCards();
	virtual void PassiveAction();
	virtual void ChooseBuildingToBuild();
	virtual void pickBuilding( string choice );
	virtual void Build( string );
	virtual void NextRole();
	bool HasPlayer();
	shared_ptr<Player> getPlayer();
	string getName();
	void setPlayer(shared_ptr<Player> player);
	bool UsedAction();
	bool UsedStandardAction();
	bool UsedPassive();
	bool UsedBuildAction();
	virtual void PlayerChoseOption( string chosenOption );

	virtual void DoneBuilding();

	bool murdered, stolen;
};

