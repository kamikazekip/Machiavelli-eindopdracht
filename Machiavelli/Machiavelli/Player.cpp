//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//
#include <algorithm> 
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

void Player::addBuildings( vector<shared_ptr<Building>> buildings )
{
	for( int c = 0; c < buildings.size(); c++ )
		hand.push_back( buildings.at( c ) );
}

void Player::addBuilding( shared_ptr<Building> building )
{
	hand.push_back( building );
}

void Player::removeBuilding(shared_ptr<Building> buildings)
{
	hand.erase(remove(hand.begin(), hand.end(), buildings), hand.end());
}

void Player::clearHand()
{
	hand.clear();
}

void Player::addGold( int newGold )
{
	gold += newGold;
}

int Player::getGold()
{
	return gold;
}

vector<shared_ptr<Building>> Player::getBuildings()
{
	return hand;
}

vector<shared_ptr<Building>> Player::getTableBuildings()
{
	return table;
}

void Player::removeTableBuilding(shared_ptr<Building> building)
{
	table.erase(remove(table.begin(), table.end(), building), table.end());
}

void Player::buildBuilding( shared_ptr<Building> building )
{
	hand.erase( remove( hand.begin(), hand.end(), building ), hand.end() );
	table.push_back( building );
}

int Player::countScore()
{
	int score = 0;
	for (int i = 0; i < getTableBuildings().size(); i++)
	{
		score = score + getTableBuildings().at(i)->getScore();
	}
	return score;
}
