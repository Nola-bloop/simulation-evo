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
*   J'ai d�cid� d'utiliser les std::map parce que la manipulation est beaucoup plus facile qu'avec des tableaux/vecteurs ou des strings.
*   J'ai besoin de savoir rapidement il y a combien de chaque lettre et les std::map permettent de le faire. �a facilite aussi la
*   comparaison entre deux cr�atures, par exemple, l'algorithme de reproduction (Creature::mate()) a �t� extr�mement plus facile �
*   faire parce que j'utilise des maps. J'avais commenc� mon projet avec des strings, mais je me suis vite rendu compte que �a allait
*   �tre insuportable � utiliser.
* 
* std::vector
*   J'utilise les vecteurs pour ma liste d'�v�nements (PopulationMgr::eventQueue) et pour la population (Population::creatures).
*   Les vecteurs sont une meilleure option que les tableaux normeaux, parce que la taille fluctue beaucoup, surtout celui de la
*   population. Oui, les vecteurs utilisent beaucoup de ressources, mais avec une utilisation intelligente du std::vector.reserve(),
*   on peut minimiser les d�g�ts. Avant d'utiliser le reserve, ma m�moire �tait plafonn�e, mais apr�s l'avoir ajout�, �a s'est calm�.
*   Bien vouloir remercier Morgan pour la suggestion de reserve et l'aide � la d�tection des memory leaks :,) Qu'es-ce qu'on ferait
*   sans lui?
* 
* std::ofstream & std::filesystem (fs)
*   J'avais besoin de lister et cr�er des fichier. Aussi �tre capable d'�crire � l'int�rieur. Une rapide recherche google m'�
*   dirig�e vers std::ofstream et std::filesystem. J'ai pu facilement trouver la doc officielle et comprendre le fonctionnement.
*   Je n'ai pas cherch� plus loin, puisqu'apr�s quelque tests (comme lister un dossier bidon et �crire des donn�es bidons dans un
*   fichier fra�chement cr��), je n'ai pas ressenti le besoin de trouver une solution plus efficace. Tout fonctionnait bien et je
*   me sentais � l'aise avec la mani�re de les manipuler.
*   
* srand & rand
*   J'ai essay� plusieurs m�thodes pour obtenir des valeurs al�atoires, tous trouv�s sur Stackoverflow ou la doc officielle et celle-ci
*   me parraissait la plus simple � utiliser. Elle m'a caus� des probl�me � un certain moment parce que je ne savais pas que le srand()
*   est global. Si tu call srand() plusieurs fois, ton random est tout fuck� pis j'ai pass� un bon moment � trouver l'erreur. (C'est
*   Deepseek qui m'a aid�). l'utilisation du rand() est tr�s straight-forward, donc je n'ai pas eu de probl�me de ce c�t�. Bref, j'ai
*   bien aim� cette m�thode pour faire du random parce que c'est propre, facile � lire, facile � utiliser et �a fonctionne bien. Les
*   autres m�thode que j'ai essay� �taient tous un peu weird � regarder.
* 
* Pour une explication d�taill�e de l'agorithme de reproduction, voir l'impl�mentation de la m�thode `Creature::mate()`.
*/




#include "Creature.h"
#include "Population.h"
#include "PopulationMgr.h"

//param�tres de la simulation
int population_size{1000};
int maxPopulation{ 50000 };
int maxEvents{ 4 };
time_t seed{ time(nullptr) };

std::string path;

namespace fs = std::filesystem;


void run(std::ofstream* timeline) {
    PopulationMgr mgr;
    mgr.seed = seed;
    mgr.timeline = timeline;
    mgr.path = path;
    mgr.maxPopulation = maxPopulation / 2;
    mgr.maxEvents = maxEvents;
    mgr.population = Population(population_size);
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
    timeline << "cycle,events,deaths,population,creatures\n";
    run(&timeline);
    
    timeline.close();

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
    //_CrtDumpMemoryLeaks();
}
