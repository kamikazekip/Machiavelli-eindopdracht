#include "Architect.h"
#include "Game.h"

Architect::Architect( shared_ptr<Game> game ) :Role(game)
{
	game->broadcast("Architect meldt zich!");
}


Architect::~Architect()
{
}
