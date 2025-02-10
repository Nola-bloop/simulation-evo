#pragma once

#include <map>
#include <fstream>

namespace fs = std::filesystem;

class Event
{
public:
	int duration{ 0 };
	std::map<char, int> resist;
	std::map<char, int> hurt;
	std::map<char, int> tally;
	std::ofstream logs;

	/// <summary>
	/// Tallies the generated mods, and creates the csv file
	/// </summary>
	/// <param name="path">path to write the file at</param>
	/// <param name="id">id of the event</param>
	void getTally(std::string path, int id);

	/// <summary>
	/// create a csv file for details about the event
	/// </summary>
	/// <param name="path">path to create the file</param>
	/// <param name="id">id of the event</param>
	void initOfstream(std::string path, int id);

	virtual void writeFirst();
};

