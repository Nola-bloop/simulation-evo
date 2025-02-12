#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>

/*
* Explications de mes choix de librairies
* 
* std::map
*   J'ai décidé d'utiliser les std::map parce que la manipulation est beaucoup plus facile qu'avec des tableaux/vecteurs ou des strings.
*   J'ai besoin de savoir rapidement il y a combien de chaque lettre et les std::map permettent de le faire. Ça facilite aussi la
*   comparaison entre deux créatures, par exemple, l'algorithme de reproduction (Creature::mate()) a été extrèmement plus facile à
*   faire parce que j'utilise des maps. J'avais commencé mon projet avec des strings, mais je me suis vite rendu compte que ça allait
*   être insuportable à utiliser.
* 
* std::vector
*   J'utilise les vecteurs pour ma liste d'évènements (PopulationMgr::eventQueue) et pour la population (Population::creatures).
*   Les vecteurs sont une meilleure option que les tableaux normeaux, parce que la taille fluctue beaucoup, surtout celui de la
*   population. Oui, les vecteurs utilisent beaucoup de ressources, mais avec une utilisation intelligente du std::vector.reserve(),
*   on peut minimiser les dégâts. Avant d'utiliser le reserve, ma mémoire était plafonnée, mais après l'avoir ajouté, ça s'est calmé.
*   Bien vouloir remercier Morgan pour la suggestion de reserve et l'aide à la détection des memory leaks :,) Qu'es-ce qu'on ferait
*   sans lui?
* 
* std::ofstream & std::filesystem (fs)
*   J'avais besoin de lister et créer des fichier. Aussi être capable d'écrire à l'intérieur. Une rapide recherche google m'à
*   dirigée vers std::ofstream et std::filesystem. J'ai pu facilement trouver la doc officielle et comprendre le fonctionnement.
*   Je n'ai pas cherché plus loin, puisqu'après quelque tests (comme lister un dossier bidon et écrire des données bidons dans un
*   fichier fraîchement créé), je n'ai pas ressenti le besoin de trouver une solution plus efficace. Tout fonctionnait bien et je
*   me sentais à l'aise avec la manière de les manipuler.
*   
* srand & rand
*   J'ai essayé plusieurs méthodes pour obtenir des valeurs aléatoires, tous trouvés sur Stackoverflow ou la doc officielle et celle-ci
*   me parraissait la plus simple à utiliser. Elle m'a causé des problème à un certain moment parce que je ne savais pas que le srand()
*   est global. Si tu call srand() plusieurs fois, ton random est tout fucké pis j'ai passé un bon moment à trouver l'erreur. (C'est
*   Deepseek qui m'a aidé). l'utilisation du rand() est très straight-forward, donc je n'ai pas eu de problème de ce côté. Bref, j'ai
*   bien aimé cette méthode pour faire du random parce que c'est propre, facile à lire, facile à utiliser et ça fonctionne bien. Les
*   autres méthode que j'ai essayé étaient tous un peu weird à regarder.
* 
* Pour une explication détaillée de l'agorithme de reproduction, voir l'implémentation de la méthode `Creature::mate()`.
*/




#include "Creature.h"
#include "Population.h"
#include "PopulationMgr.h"

//paramètres de la simulation
int population_size{500};
time_t seed{ time(nullptr) };

std::string path;

namespace fs = std::filesystem;


void run(std::ofstream* timeline) {
    PopulationMgr mgr;
    mgr.seed = seed;
    mgr.timeline = timeline;
    mgr.path = path;
    mgr.population = Population::Population(population_size);
    mgr.population.inspect();

    std::cout << "Enter the number of cycles to execute: ";
    std::string usrInput{ "nthn" };
    std::cin >> usrInput;

    mgr.playCycles(atoi(usrInput.c_str()));
    mgr.population.inspect();
    std::cout << "Incest Count: " << mgr.incestCount;
}

std::ofstream mkFolder() {
    path = "./simData";
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
    timeline << "cycle,event_count,deaths,population,dna-lifetime-maxLifetime-birthrate\n";
    run(&timeline);
    
    timeline.close();

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
    //_CrtDumpMemoryLeaks();
}
