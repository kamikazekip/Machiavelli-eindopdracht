#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Building.h"
#include <algorithm>
using namespace std;

class BuildingFactory
{
private:
	string buildingsFile;
	vector<shared_ptr<Building>> buildings;
public:
	BuildingFactory();
	~BuildingFactory();
	vector<shared_ptr<Building>> getStartBuildings();
};

