#include "Wizard.h"
#include "Game.h"


Wizard::Wizard( shared_ptr<Game> game ) :Role( game )
{
}


Wizard::~Wizard()
{
}

void Wizard::Action()
{
	*player << "Met wie wil je je bouwkaarten wisselen? Of wil je je bouwkaarten inwisselen voor nieuwe?";
}
