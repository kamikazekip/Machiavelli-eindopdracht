#include "BuildingFactory.h"



BuildingFactory::BuildingFactory()
{
	buildingsFile = "../Machiavelli/Bouwkaarten.csv";
	ifstream myfile( buildingsFile );
	string line;
	if( myfile.is_open() )
	{
		while( getline( myfile, line ) )
		{
			vector<string> tokens;
			string delimiter = ";";

			size_t pos = 0;
			string token;
			while( ( pos = line.find( delimiter ) ) != string::npos )
			{
				token = line.substr( 0, pos );
				line.erase( 0, pos + delimiter.length() );
				tokens.push_back( token );
			}
			shared_ptr<Building> building{ new Building( tokens[0], stoi( tokens[1] ), tokens[2] ) };
			if( tokens.size() > 3 )
			{
				building->setDescription( tokens[3] );
			}
			buildings.push_back( building );
		}
		myfile.close();
	}
	else
		cout << "Unable to open buildings file!\n";
}


BuildingFactory::~BuildingFactory()
{

}

vector<shared_ptr<Building>> BuildingFactory::getStartBuildings()
{

	return buildings;
}
