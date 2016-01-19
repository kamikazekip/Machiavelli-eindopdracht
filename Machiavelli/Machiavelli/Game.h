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
typedef void ( Game::*sequence_function )( shared_ptr<Player> currentPlayer );
typedef void ( Role::*role_function )( );

namespace machiavelli
{
	const int tcp_port { 1080 };
	const string prompt { "machiavelli_client> " };
	const string endl { "\r\nmachiavelli_client> " };
	const string rn { "\r\n" };
	const string indent{ "  " };
}
enum GameState { GameState_PreGame, GameState_Choosing_Role, GameState_Removing_Role, GameState_In_Game };

class Game
{
private:
	map<string, game_function> commands;
	map<string, pair<role_chosing_function, shared_ptr<Role>>> roleOptions;
	map<string, role_function> roleFunctions;
	shared_ptr<Player> turn;
	shared_ptr<Player> king;
	shared_ptr<Player> otherPlayer;
	vector<shared_ptr<Player>> players;
	vector<shared_ptr<Role>> roles;
	vector<shared_ptr<Building>> buildingStack;
	unique_ptr<BuildingFactory> buildingFactory;
	vector<shared_ptr<Role>> rolePool;
	vector<pair<sequence_function, shared_ptr<Player>>> sequence;
	shared_ptr<Role> currentRole;

	GameState gameState;

	void chooseOption( ClientCommand command );
	void gameStart();
	void chooseRoles();
	void pickedRole( shared_ptr<Role> choice );
	void removedRole(shared_ptr<Role> choice);
	void removeRole( shared_ptr<Player> player );
	void pickRole( shared_ptr<Player> player );
	void nextSegment();
	void handleRole( shared_ptr<Role> role );
	void nextRole();
	void startPlayRound();
	void cheat( shared_ptr<Player> player );
public:
	Game();
	~Game();
	void handleCommand( ClientCommand command, shared_ptr<Player> player );
	void addPlayer( shared_ptr<Player> player );
	void removePlayer( shared_ptr<Player> player );
	void broadcast( string message );
	void look( shared_ptr<Player> player );
	void setNewKing( shared_ptr<Player> newKing );
	vector<shared_ptr<Building>> getBuildingsFromStack( int amount );
};

