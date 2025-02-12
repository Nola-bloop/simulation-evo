#pragma once

#include "Creature.h"
#include "Event.h"

#include <map>
#include <vector>

class Population
{
public:
	/// <summary>
	/// Instantiate an empty population
	/// </summary>
	Population();

	/// <summary>
	/// Instanciate a population with the specified size
	/// </summary>
	/// <param name="">The size of the population</param>
	Population(int size);



	/// <summary>
	/// prints the population to the console
	/// </summary>
	void inspect();

	/// <summary>
	/// Add a creature to the population
	/// </summary>
	/// <param name=""></param>
	void addCreature(Creature);

	/// <summary>
	/// Play an event
	/// </summary>
	/// <param name="">The event to play</param>
	int playEvent(Event*);

	/// <summary>
	/// Getter of creatures. returns a vector
	/// </summary>
	/// <returns>the creatures of the population (std::vector<Creature>)</returns>
	std::vector<Creature> getCreatures();

	/// <summary>
	/// returns the ammount of creatures
	/// </summary>
	/// <returns></returns>
	int getCount();

	/// <summary>
	/// Mates all creatures that are ready with random creatures from the population
	/// </summary>
	/// <returns>The number of incest that happened</returns>
	int mateSeason(int year, int maxPop);

	/// <summary>
	/// Destroy all the creatures that are ready to die and returns the number of dead creatures
	/// </summary>
	int purge();

	/// <summary>
	/// deal x amount of damage to each creature
	/// </summary>
	/// <param name=""></param>
	void damage(int);
private:
	int count{ 0 };
	std::vector<Creature> creatures;
	std::map<char, int> stats;
};

