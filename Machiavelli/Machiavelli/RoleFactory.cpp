#include "RoleFactory.h"
#include "Assassin.h"
#include "Priest.h"
#include "Condottiere.h"
#include "King.h"
#include "Thief.h"
#include "Wizard.h"
#include "Architect.h"
#include "Merchant.h"

RoleFactory::RoleFactory( shared_ptr<Game> game )
{
	this->game = game;
	fillRoleMap();
	rolesFile = "../Machiavelli/Karakterkaarten.csv";
	ifstream myfile(rolesFile);
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector<string> tokens;
			string delimiter = ";";

			size_t pos = 0;
			string token;
			while ((pos = line.find(delimiter)) != string::npos)
			{
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				tokens.push_back(token);
			}
			shared_ptr<Role> role = roleMap.at(tokens[1]);
			role->setNameTurn(tokens[1], stoi(tokens[0]));
			roles.push_back(role);
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open roles file!\n";
	}
}


RoleFactory::~RoleFactory()
{
}

void RoleFactory::fillRoleMap()
{
	roleMap.insert(pair<string, shared_ptr<Role>>("Moordenaar", shared_ptr<Role> { new Assassin(game) }));
	roleMap.insert(pair<string, shared_ptr<Role>>("Dief", shared_ptr<Role> { new Thief( game ) }));
	roleMap.insert(pair<string, shared_ptr<Role>>("Magier", shared_ptr<Role> { new Wizard( game ) }));
	roleMap.insert(pair<string, shared_ptr<Role>>("Koning", shared_ptr<Role> { new King( game ) }));
	roleMap.insert(pair<string, shared_ptr<Role>>("Prediker", shared_ptr<Role> { new Priest( game ) }));
	roleMap.insert(pair<string, shared_ptr<Role>>("Koopman", shared_ptr<Role> { new Merchant( game ) }));
	roleMap.insert(pair<string, shared_ptr<Role>>("Bouwmeester", shared_ptr<Role> { new Architect( game ) }));
	roleMap.insert(pair<string, shared_ptr<Role>>("Condottiere", shared_ptr<Role> { new Assassin( game ) }));
}

vector<shared_ptr<Role>> RoleFactory::getRoles()
{
	return roles;
}