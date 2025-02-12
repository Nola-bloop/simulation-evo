#include "Disaster.h"
#include "Creature.h"

#include <stdlib.h>
#include <filesystem>
#include <time.h>


Disaster::Disaster(std::string path, int id) {
	this->duration = rand() % 5 + 1;

	for (int i = 0; i < 26; i++) {
		if (rand() % 4 == 0) {
			if (rand() % 50 == 0) {
				this->hurt[Creature::codes[i]] = rand() % 5 + 2;
			}
			else this->hurt[Creature::codes[i]] = rand() % 5;

			if (rand() % 50 == 0) {
				this->resist[Creature::codes[i]] = rand() % 5 + 2;
			}
			else this->resist[Creature::codes[i]] = rand() % 5;
		}
	}
	this->getTally(path, id);
}
void Disaster::writeFirst()
{
	this->logs << "Disaster;" << this->duration << ";";
}