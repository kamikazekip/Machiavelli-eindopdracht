#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include "Role.h"

class Game;
using namespace std;

class RoleFactory
{
private: 
	string rolesFile;
	vector<shared_ptr<Role>> roles;
	void fillRoleMap();
	map<string, shared_ptr<Role>> roleMap;
	shared_ptr<Game> game;
public:
	RoleFactory( shared_ptr<Game> game );
	vector<shared_ptr<Role>> getRoles();
	~RoleFactory();
};

