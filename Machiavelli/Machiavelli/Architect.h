#pragma once
#include "Role.h"

class Architect : public Role
{
public:
	Architect( shared_ptr<Game> game );
	~Architect();
	void PassiveAction();
	void Build( string building );
	void DoneBuilding();
private: 
	int buildingCounter;
};

