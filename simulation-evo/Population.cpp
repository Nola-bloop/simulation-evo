#include "Population.h"

#include <iostream>

Population::Population() {
}
Population::Population(int size) {
	this->creatures.reserve(size);
    for (int i = 0; i < size; i++) {
        this->addCreature(Creature());
    }
}

void Population::inspect() {

	
	for (size_t i = 0; i < this->creatures.size(); i++) {
		std::cout << "[" << i << "] " << this->creatures[i].getDnaString() << "\n";
	}

	std::map<char, bool> displayed = {};

	
	std::map<char, int>::iterator it;
	for (it = this->stats.begin(); it != this->stats.end(); it++) {

		//sort by qty
		char highest = ' ';
		std::map<char, int>::iterator it2;
		for (it2 = this->stats.begin(); it2 != this->stats.end(); it2++) {
			if (!displayed[it2->first]) {
				if (highest == ' ') {
					highest = it2->first;
				}
				else if (it2->second > stats[highest]) {
					highest = it2->first;
				}
			}
		}

		//(X;###)
		std::cout << "(" << highest << ";" << this->stats[highest] << ")";
		displayed[highest] = true;

		//count how many creatures hold this gene
		int geneCount{ 0 };
		for (size_t i = 0; i < this->creatures.size(); i++) {
			std::map<char, int> map{ this->creatures[i].getDna() };
			if (this->creatures[i].getDna()[highest] > 0) {
				geneCount++;
			}
		}
		std::cout << " held by " << geneCount << " creatures.\n";
	}
	std::cout << "Population: " << this->count << "\n";
}

void Population::addCreature(Creature toAdd) {
	this->creatures.push_back(toAdd);
	std::string str = toAdd.getDnaString();
	for (size_t i = 0; i < str.length(); i++) {
		this->stats[str[i]] += 1;
	}
	this->count++;
}

int Population::playEvent(Event* event) {
	int kills{ 0 };
	for (size_t i = 0; i < this->creatures.size(); i++) {
		kills += this->creatures[i].applyMod(event->tally);
	}
	return kills;
}

std::vector<Creature> Population::getCreatures() {
	return this->creatures;
}

int Population::getCount() {
	return this->count;
}

int Population::mateSeason(int year, int maxPop) {
	int incestCount{ 0 };
	this->creatures.reserve(maxPop * 2);
	for (int i{ 0 }; i < this->count; i++) {
		if (this->creatures[i].readyToProc) {
			Creature child;
			child = this->creatures[i].mate(this->creatures[rand() % this->count], year);
			this->addCreature(child);
			if (child.getIncestCombo() > 0) 
				incestCount++;
		}
	}
	return incestCount;
}

int Population::purge() {
	int deathCount{ 0 };
	for (int i = 0; i < this->count; i++)
		if (this->creatures[i].readyToDie) {
			deathCount++;
			std::map<char, int> dnaRun = creatures[i].getDna();
			std::map<char, int>::iterator it;
			for (it = dnaRun.begin(); it != dnaRun.end(); it++)
				this->stats[it->first] -= it->second;
			this->creatures.erase(this->creatures.begin() + i);
			i--;
			this->count--;
		}
	this->creatures.shrink_to_fit();
	return deathCount;
}

void Population::damage(int dmg) {
	for (int i = 0; i < this->count; i++) {
		this->creatures[i].lifetime -= dmg;
		if (this->creatures[i].lifetime <= 0) {
			this->creatures[i].readyToDie = true;
		}
	}
}