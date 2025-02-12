#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>

#include "Creature.h"
#include "Population.h"
#include "PopulationMgr.h"

//param�tres de la simulation
int population_size{500};
time_t seed{ time(nullptr) };

std::string path;

namespace fs = std::filesystem;


void run(std::ofstream* timeline) {
    PopulationMgr mgr;
    mgr.seed = seed;
    mgr.timeline = timeline;
    mgr.path = path;
    mgr.population = Population(population_size);
    mgr.population.inspect();

    std::cout << "Enter the number of cycles to execute: ";
    std::string usrInput{ "nthn" };
    std::cin >> usrInput;

    mgr.playCycles(atoi(usrInput.c_str()));
    mgr.population.inspect();
    std::cout << "Incest Count: " << mgr.incestCount;

    *timeline << mgr.incestCount;
}

std::ofstream mkFolder() {
    path = "../sims";
    int count{ 0 };
    for (const auto& entry : fs::directory_iterator(path)) {
        count++;
    }
    path += "/sim" + std::to_string(count);
    fs::create_directories(path);
    //fs::create_directories(path+"/events");

    std::ofstream outfile(path+"/timeline.csv");
    return outfile;
}

int main()
{
    srand(static_cast<unsigned int>(seed));

    std::ofstream timeline = mkFolder();
    run(&timeline);
    
    timeline.close();

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
    //_CrtDumpMemoryLeaks();
}
