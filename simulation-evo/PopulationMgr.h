#pragma once

#include "Population.h"
#include "Event.h"
#include "Epidemic.h"
#include "Disaster.h"

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>

namespace fs = std::filesystem;

struct PopulationMgr
{
	//functionnal variables
	Population population = Population::Population();
	std::vector<Event*> eventQueue{};
	int cycle{ 0 };
	time_t seed = time(NULL);
	std::ofstream* timeline;
	std::string path;
	int lastCyclePop{ 0 };
	int incestCount{ 0 };

	//controllers
	bool verbose{ false };
	int maxPopulation{ 10000 };
	int epidemicChance{ 30 }; //higher the number, the rarer it is
	int disasterChance{ 20 }; //"
	int maxEvents{ 4 };

	~PopulationMgr();

	/// <summary>
	/// Make the population grow for x cycles
	/// </summary>
	/// <param name="cycles">number of cycles to execute</param>
	void playCycles(int cycles);

	void generateLog(int deaths);
};

