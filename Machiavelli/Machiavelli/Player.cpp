//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.hpp"
#include <Windows.h>
using namespace std;

const Player& Player::operator<<( const char c ) const
{
	client->write( c );
	return *this;
}

const Player& Player::operator<<( const char* message ) const
{
	client->write( string{ message } );
	return *this;
}

const Player& Player::operator<<( const string& message ) const
{
	client->write( message );
	return *this;
}

void Player::addBuilding(shared_ptr<Building> building)
{
	hand.push_back( building );
}

void Player::addBuildings( vector<shared_ptr<Building>> buildings )
{
	for( int c = 0; c < buildings.size(); c++ )
		hand.push_back( buildings.at( c ) );
}

void Player::addGold( int newGold )
{
	gold += newGold;
}

vector<shared_ptr<Building>> Player::getBuildings()
{
	return buildings;
}
