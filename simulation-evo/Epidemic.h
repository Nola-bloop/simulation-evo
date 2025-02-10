#pragma once

#include <map>

#include "Event.h"

/// <summary>
/// Epidemics are disasters that last a lot longer, minimum of 20 cycles. They have smaller effects
/// </summary>
class Epidemic : public Event
{
public:
	/// <summary>
	/// Ctor for an Epidemic, generates a csv file too
	/// </summary>
	/// <param name="path">path to write at</param>
	/// <param name="id">id of the epidemic</param>
	Epidemic(std::string path, int id);

	void writeFirst() override;
};

