#include "Event.h"

#include <map>
#include <string>

void Event::getTally(std::string path, int id) {
	initOfstream(path, id);

	this->writeFirst();

	std::map<char, int>::iterator it;
	for (it = this->hurt.begin(); it != this->hurt.end(); it++) {
		this->tally[it->first] -= it->second;
	}

	for (it = this->resist.begin(); it != this->resist.end(); it++) {
		this->tally[it->first] -= it->second;
	}

	std::string out{ "" };
	for (it = this->tally.begin(); it != this->tally.end(); it++) {
		out += it->first + std::to_string(it->second) + ",";
	}
	out = out.substr(0, out.length() - 1);
	out += "\n";
	this->logs << out;
}

void Event::initOfstream(std::string path, int id)
{
	this->logs = std::ofstream(path+"/event"+std::to_string(id)+".csv");
}

void Event::writeFirst()
{
	this->logs << "unknown event type";
}
