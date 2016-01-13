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
			string delimiter = ";";

			size_t pos = 0;
			string token;
			while( ( pos = line.find( delimiter ) ) != string::npos )
			{
				token = line.substr( 0, pos );
				line.erase( 0, pos + delimiter.length() );

			}
		}
		myfile.close();
	}
	else
		cout << "Unable to open buildings file!\n";
}


BuildingFactory::~BuildingFactory()
{

}
