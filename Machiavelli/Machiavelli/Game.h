#pragma once
#include <vector>
#include "Player.hpp"
#include "Role.h"
#include <memory>
#include "Building.h"
#include "RoleFactory.h"
#include "BuildingFactory.h"
#include <string>
#include <map>
#include "ClientCommand.h"
#include <iostream>
#include "Socket.h"
#include <random>

using namespace std;
class Game;

typedef void ( Game::*game_function )( shared_ptr<Player> player );
typedef void ( Game::*role_chosing_function )( shared_ptr<Role> choice );

namespace machiavelli
{
	const int tcp_port { 1080 };
	const string prompt { "machiavelli_client> " };
	const string endl { "\r\nmachiavelli_client> " };
	const string rn { "\r\n" };
}
enum GameState { GameState_PreGame, GameState_Choosing_Role };

class Game
{
private:
	map<string, game_function> commands;
	map<string, pair<role_chosing_function, shared_ptr<Role>>> roleOptions;
	shared_ptr<Player> turn;
	shared_ptr<Player> king;
	vector<shared_ptr<Player>> players;
	vector<shared_ptr<Role>> roles;
	vector<shared_ptr<Building>> buildingStack;
	unique_ptr<BuildingFactory> buildingFactory;

	GameState gameState;
	void chooseOption( ClientCommand command );
	void gameStart();
	void chooseRoles();
	void pickRole( shared_ptr<Role> choice );
public:
	Game();
	~Game();
	void handleCommand( ClientCommand command, shared_ptr<Player> player );
	void addPlayer( shared_ptr<Player> player );
	void removePlayer( shared_ptr<Player> player );
	void broadcast( string message );
	void look( shared_ptr<Player> player );

};

