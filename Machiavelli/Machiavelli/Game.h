#pragma once
#include <vector>
#include "Player.hpp"
#include "Role.h"
#include <memory>
#include "Building.h"

using namespace std;

class Game
{
private:
	vector<shared_ptr<Player>> players;
	vector<shared_ptr<Role>> roles;
	vector<shared_ptr<Role>> rolePool;
	vector<shared_ptr<Building>> buildingStack;
public:
	Game();
	~Game();
};

