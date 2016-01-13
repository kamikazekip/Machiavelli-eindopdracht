//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.hpp"
using namespace std;

void Player::addBuilding(shared_ptr<Building> building)
{
	hand.push_back( building );
}

void Player::addBuildings( vector<shared_ptr<Building>> buildings )
{
	for( int c = 0; c < buildings.size(); c++ )
		hand.push_back( buildings.at( c ) );
}