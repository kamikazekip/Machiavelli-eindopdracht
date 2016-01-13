//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include <vector>
#include <string>
#include <memory>
#include "Socket.h"
#include "Building.h"


using namespace std;

class Player {
public:
	shared_ptr<Socket> client;
	Player() {}
	Player( const std::string& name, shared_ptr<Socket> client ) : name{ name }, client{ client }
	{
	}
	
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }
	vector<shared_ptr<Building>> table;
	void addBuildings(vector<shared_ptr<Building>> buildings);
	void addBuilding( shared_ptr<Building> building );
	void clear();
private:
	std::string name;
	int gold;
	vector<shared_ptr<Building>> hand;
};

#endif /* Player_hpp */
