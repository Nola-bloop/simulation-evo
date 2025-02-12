#include "PopulationMgr.h"

#include <iostream>
#include <stdlib.h>

PopulationMgr::~PopulationMgr()
{
	// Properly deallocate memory for events in the eventQueue
	for (Event* event : eventQueue) {
		event->logs.close();
		delete event;
	}
}

void PopulationMgr::playCycles(int cycles) {
	// Tasks:
	//- create events by chance
	//- play events
	//- Deal one damage to all
	//- procreate creatures that are ready
	//- kill creatures waiting to die


	for (int i = 0; i < cycles; i++) {
		std::cout << "" << (float)i/(float)cycles*100 << "%" << "(" << this->population.getCount() << ")" << "\n";

		//create events if necessary
		if (this->verbose) std::cout << "    Generating events..." << "\n";
		if (rand() % this->epidemicChance == 0) {
			Epidemic* newEpi = new Epidemic(this->path,this->eventQueue.size());
			if (this->verbose) std::cout << "Creating a pandemic... {" << this->cycle << "} " << newEpi->duration <<" cycles; " << " \n";
			eventQueue.push_back(newEpi);
		}
		if (rand() % this->disasterChance == 0) {
			if (this->verbose) std::cout << "Creating a disaster... {" << this->cycle << "}\n";
			Disaster* newDis = new Disaster(this->path, this->eventQueue.size());
			eventQueue.push_back(newDis);
		}

		//apply events
		if (this->verbose) std::cout << "    Applying events..." << "\n";
		for (size_t j = 0; j < eventQueue.size(); j++) {
			eventQueue[j]->logs << this->cycle << "," << this->population.playEvent(eventQueue[j]) << "\n";
			eventQueue[j]->duration -= 1;

			//if event is done, erase it from the event queue
			if (eventQueue[j]->duration <= 0) {
				eventQueue[j]->logs.close();
				delete eventQueue[j];
				eventQueue.erase(eventQueue.begin() + j);
				j--;
			}
		}

		if (this->verbose) std::cout << "    Applying time damage..." << "\n";
		this->population.damage(1);

		//procreate
		if (this->verbose) std::cout << "    Running mating season..." << "\n";
		if (this->population.getCount() < this->maxPopulation) this->incestCount += this->population.mateSeason(this->cycle, this->maxPopulation);

		//trigger all deaths
		if (this->verbose) std::cout << "    Running purge..." << "\n";
		int deaths = this->population.purge();


		this->cycle++;

		this->generateLog(deaths);

		this->lastCyclePop = this->population.getCount();
	}
}

void PopulationMgr::generateLog(int deaths)
{
	*this->timeline << this->cycle << ",";
	*this->timeline << this->eventQueue.size() << ",";
	*this->timeline << deaths << ",";
	*this->timeline << this->population.getCount() << ",";
	
	
	std::vector<Creature> creatures = this->population.getCreatures();
	for (size_t i = 0; i < creatures.size(); i++)
		if (i < creatures.size() - 1) {
			*this->timeline << creatures[i].toString() << ":";
		}else
			*this->timeline << creatures[i].getDnaString();

	*this->timeline << "\n";
}
