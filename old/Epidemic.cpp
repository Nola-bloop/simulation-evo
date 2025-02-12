#include "Epidemic.h"
#include "Creature.h"

#include <stdlib.h>
#include <filesystem>
#include <time.h>

Epidemic::Epidemic(std::string path, int id) {
	this->duration = rand() % 200 + 30;

	for (int i = 0; i < 26; i++) {
		if (rand() % 5 == 0) {
			this->hurt[Creature::codes[i]] = rand() % 5;
		}

		if (rand() % 5 == 0) {
			this->resist[Creature::codes[i]] = rand() % 5;
		}
	}

	this->getTally(path, id);
}

void Epidemic::writeFirst()
{
	this->logs << "Epidemic;" << this->duration << ";";
}
