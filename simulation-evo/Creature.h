#pragma once

#include <map>
#include <string>
#include <stdlib.h>
#include <time.h>

class Creature
{
public:
	static const char codes[26];
	static long countId;

	int lifetime{ 30 };
	bool readyToProc{ false };
	bool readyToDie{ false };

	void creerModele();

	/// <summary>
	/// Create a creature with starting values
	/// </summary>
	/// <param name="dna">it's DNA, containing only letters A-Z, assign a number to each letter</param>
	/// <param name="generation">How many people were born to birth this creature (just +1 the dad's gen)</param>
	/// <param name="birth">In which cycle was this born</param>
	/// <param name="incestCount">Number of incest cycles prior to this one</param>
	Creature(std::map<char, int> dna, int generation, int birth, int incestCount);

	/// <summary>
	/// Instantiate a creature with random dna, gen 0, and dob 0. lifetime of 20, birthrate of 5
	/// </summary>
	Creature();

	/// <summary>
	/// Create a creature with predefined everything.
	/// </summary>
	/// <param name="dna">it's DNA, containing only letters A-Z, assign a number to each letter</param>
	/// <param name="generation">How many people were born to birth this creature (just +1 the dad's gen)</param>
	/// <param name="birth">In which cycle was this born</param>
	/// <param name="incestCount">Number of incest cycles prior to this one</param>
	/// <param name="lifetime">Lifetime to set. Will still be affected by incest counter-measures.</param>
	/// <param name="birthrate">birthrate of the creature. lower the number, quicker the reproduction.</param>
	Creature(std::map<char, int> dna, int generation, int birth, int incestCount, int lifetime, int birthrate);



	/// <summary>
	/// return a formatted string of the creature
	/// </summary>
	/// <returns></returns>
	std::string toString();

	/// <summary>
	/// gets the dna map
	/// </summary>
	/// <returns>the dna map of the creature</returns>
	std::map<char, int> getDna();

	/// <summary>
	/// gets the dna string
	/// </summary>
	/// <returns>the dna string of the creature</returns>
	std::string getDnaString();

	/// <summary>
	/// Will kill or not a creature depending on the sent modifiers
	/// </summary>
	/// <param name="">The modifier do apply</param>
	/// <returns>the number of creatures killed by this mod</returns>
	int applyMod(std::map<char, int>);

	/// <summary>
	/// Create a child sharing some of the parent's dna
	/// </summary>
	/// <param name="other">the other parent</param>
	/// <param name="year">the current year (cycle)</param>
	/// <returns>the child (Creature)</returns>
	Creature mate(Creature other, int year);

	/// <summary>
	/// Gets the incest combo of the creature
	/// </summary>
	/// <returns>an int value of the incest combo</returns>
	int getIncestCombo();
private:
	long long id;
	std::map<char,int> dna;
	int generation;
	int birth;
	time_t seed{ time(NULL) };
	std::map<char, int> DoT;
	int incestCombo{ 0 };
	int defLifetime{ 30 };
	int birthrate{ 5 };

	void ctorShared();
	std::map<char, int> getRandomDna() const;
};