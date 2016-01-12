#pragma once
#include <vector>
#include "Player.hpp"
#include "Role.h"
#include <memory>
#include "Building.h"
#include "ClientCommand.h"
#include <iostream>
#include "Socket.h"

using namespace std;
namespace machiavelli
{
	const int tcp_port { 1080 };
	const string prompt { "machiavelli_client> " };
	const string endl { "\r\nmachiavelli_client> " };
	const string rn { "\r\n" };
}

class Game
{
private:
	shared_ptr<Player> turn;
	vector<shared_ptr<Player>> players;
	vector<shared_ptr<Role>> roles;
	vector<shared_ptr<Role>> rolePool;
	vector<shared_ptr<Building>> buildingStack;
public:
	Game();
	~Game();
	void handleCommand( ClientCommand command, shared_ptr<Player> player );
	void addPlayer( shared_ptr<Player> player );
	void removePlayer( shared_ptr<Player> player );
	void broadcast( string message );
};

