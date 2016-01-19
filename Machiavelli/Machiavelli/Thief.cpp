#include "Thief.h"
#include "Game.h"


Thief::Thief( shared_ptr<Game> game ) :Role( game )
{
}


Thief::~Thief()
{
}

void Thief::SpecialAction()
{
	Role::SpecialAction();
	*player << "Wie zou je graag willen bestelen?";
}
