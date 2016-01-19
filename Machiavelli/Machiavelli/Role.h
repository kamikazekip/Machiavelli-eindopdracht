#pragma once
#include "Player.hpp"
#include <memory>
#include <string>

class Game;
using namespace std;

class Role
{
private:
	shared_ptr<Player> player;
	string name;
	int turn;
	shared_ptr<Game> game;
public:
	Role( shared_ptr<Game> game );
	~Role();
	void virtual Action();
	void setNameTurn(string name, int turn);
	string getName();
	void setPlayer(shared_ptr<Player> player);
	shared_ptr<Player> getPlayer();
};

