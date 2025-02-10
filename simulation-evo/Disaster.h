#pragma once

#include <map>

#include "Event.h"

/// <summary>
/// A disaster is something that will temporarily kill creatures depending on some parameters
/// </summary>
class Disaster : public Event
{
public:
	/// <summary>
	/// Ctor for Disaster, will also create a csv file
	/// </summary>
	/// <param name="path">path to make the file at</param>
	/// <param name="id">id of the disaster</param>
	Disaster(std::string path, int id);

	void writeFirst() override;
};