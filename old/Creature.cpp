#include "Creature.h"

#include <stdlib.h>
#include <time.h>
#include <string>
#include <math.h>
#include <vector>
#include <iostream>
#include <filesystem>

const char Creature::codes[26] = {
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z'
};

Creature::Creature(std::map<char, int> dna, int generation, int birth, int incestCount = 0) {
	this->ctorShared();
	this->dna = dna;
	this->generation = generation;
	this->birth = birth;

	for (int i = 0; i < incestCount; i++) {
		this->lifetime * 0.66;
		this->defLifetime * 0.66;
	}
}

Creature::Creature() { this->ctorShared(); }

std::map<char, int> Creature::getDna() {
	return this->dna;
}
std::string Creature::getDnaString() {
	std::string out{ "" };
	std::map<char, int>::iterator it;
	for (it = this->dna.begin(); it != this->dna.end(); it++) {
		for (int i = 0; i < it->second; i++)
			out += it->first;
	}
	return out;
}

int Creature::applyMod(std::map<char, int> mods) {
	// where x is the count in the dna string and y is the damage
	// if y is negative:
	//		if higher or Eq than x*5 kill instantly
	//		elseif higher than x, add DoT
	//		else do nothing
	// 
	// if y is positive:
	//		remove DoTs
	//		if higher than x*5, procreate with random and gain 5 pts

	//then:
	//apply DoT

	int kills{ 0 };

	int mult{ 5 };
	std::map<char, int>::iterator it;
	for (it = mods.begin(); it != mods.end(); it++) {
		//check if positive or negative
		if (it->second > 0) {
			//positive
			this->DoT[it->first] = 0; //rm DoT
			if (it->second >= this->dna[it->first] * mult) {
				//proc and lifetime boost
				this->readyToProc = true;
				this->lifetime += 5;

				//clamp lifetime to max
				if (this->lifetime > this->defLifetime) 
					this->lifetime -= this->lifetime - this->defLifetime;
			}
		}
		else {
			//negative
			int mod{ std::abs(it->second) };
			if (it->second >= this->dna[it->first] * mult) {
				//kill
				this->readyToDie = true;
			}
			else if (it->second >= this->dna[it->first]) {
				//add DoT
				this->DoT[it->first] += it->second/2;
			}
		}

		//apply DoT
		if (!this->readyToDie) {
			if (this->DoT[it->first] > 0) {
				this->lifetime -= 1;
				this->DoT[it->first] -= 1;
			}
		}
	}

	if (this->lifetime % 5 == 0) this->readyToProc = true;

	if (this->readyToDie) return 1;
	else return 0;
}

Creature Creature::mate(Creature other, int year) {
	this->readyToProc = false;
	other.readyToProc = false;

	std::map<char, int> parent1{ this->dna };
	std::map<char, int> parent2{ other.dna };
	std::map<char, int> mutation{ this->getRandomDna() };
	std::vector<char> commons;
	int  incestCombo{ 0 };

	//get random incest combo
	if (this->incestCombo > 0 && other.incestCombo > 0 && other.getDnaString() == this->getDnaString()) {
		if (rand() % 2 == 0) {
			incestCombo = this->incestCombo;
		}
		else {
			incestCombo = other.incestCombo;
		}
	}

	std::map<char, int> childDna;
	int childDnaTotal{ 0 };
	std::map<char, int>::iterator it;
	if (incestCombo <= 0) {
		//get mutuals and add it to child DNA
		for (it = parent1.begin(); it != parent1.end(); it++) {
			if (parent2[it->first] > 0 && parent1[it->first] > 0) {
				parent1[it->first]--;
				parent2[it->first]--;
				childDna[it->first]++;
				childDnaTotal++;
			}
		}
	}

	//generate the rest of the DNA
	//by starting to tallying all the dnas
	for (it = parent1.begin(); it != parent1.end(); it++) {
		for (int i = 0; i < it->second; i++) {
			commons.push_back(it->first);
		}
	}
	for (it = parent2.begin(); it != parent2.end(); it++) {
		for (int i = 0; i < it->second; i++) {
			commons.push_back(it->first);
		}
	}
	for (it = mutation.begin(); it != mutation.end(); it++) {
		for (int i = 0; i < it->second; i++) {
			commons.push_back(it->first);
		}
	}

	//then randomly pick dna from the tally (commons)
	for (int i = childDnaTotal; i < 8; i++) {
		int randPos = rand() % commons.size();
		char newPart = commons[randPos];
		commons.erase(commons.begin() + randPos);

		childDna[newPart] += 1;
	}
	
	Creature child(childDna, this->generation, year, incestCombo);
	for (int i{ 0 }; i < incestCombo; i++) {
		this->lifetime *= 0.66;
		this->defLifetime *= 0.66;
	}
	return child;
}

int Creature::getIncestCombo()
{
	return this->incestCombo;
}





void Creature::ctorShared() {
	this->dna = this->getRandomDna();
	this->generation = 0;
	this->birth = 0;
}

std::map<char, int> Creature::getRandomDna() const {
	std::map<char, int> newDna;
	for (int i = 0; i < 8; i++) {
		int rnd = rand() % 26;
		newDna[Creature::codes[rnd]] += 1;
		//std::cout << "[" << i << "]" << Creature::codes[rnd] << "\n";
	}
	return newDna;
}