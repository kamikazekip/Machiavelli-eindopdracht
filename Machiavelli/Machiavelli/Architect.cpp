#include "Architect.h"
#include "Game.h"

Architect::Architect( shared_ptr<Game> game ) :Role(game)
{
}


Architect::~Architect()
{
}

void Architect::PassiveAction()
{
	Role::PassiveAction();
	
}