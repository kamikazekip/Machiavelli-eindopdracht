#include "Assassin.h"
#include "Game.h"


Assassin::Assassin( shared_ptr<Game> game ) :Role( game )
{
}


Assassin::~Assassin()
{
}

void Assassin::SpecialAction()
{
	Role::SpecialAction();
	*player << "Wie zou je graag willen vermoorden?";
}