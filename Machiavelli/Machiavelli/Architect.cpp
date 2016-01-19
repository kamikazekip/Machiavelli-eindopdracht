#include "Architect.h"
#include "Game.h"

Architect::Architect( shared_ptr<Game> game ) :Role(game)
{
	buildingCounter = 0;
	usedAction = true;
}


Architect::~Architect()
{
}

void Architect::PassiveAction()
{
	Role::PassiveAction();
	player->addBuildings(game->getBuildingsFromStack(2));
}

void Architect::Build( string building )
{
	buildingCounter++;
	Role::Build( building );
	usedBuildAction = false;
}

void Architect::DoneBuilding()
{
	if( buildingCounter > 2 )
		usedBuildAction = true;
	game->handleCurrentRole();
}
	