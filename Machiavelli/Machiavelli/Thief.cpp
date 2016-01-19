#include "Thief.h"
#include "Game.h"


Thief::Thief( shared_ptr<Game> game ) :Role( game )
{
}


Thief::~Thief()
{
}

void Thief::Action()
{
	*player << "Wie zou je graag willen bestelen?";
}
