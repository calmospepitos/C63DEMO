#include <iostream>
#include "Patate.h"

using namespace std;

// #include: copie-colle le contenu entier d'un fichier
// En pratique, sert à importer le la déclaration des symboles
int main()
{
    Patate p;

    #include "Nefaitpasca.h"
    std::cout << "Hello World!\n";
    std::cout << "pi: " << PI << endl;
    std::cout << "Circonference de 4.0f: " << FORMULE_CIRCONFERENCE(4.0f) << endl;
    //std::cout << "Circonference de Coucou!: " << FORMULE_CIRCONFERENCE("Coucou!") << endl;

    std::cout << "Fichier:" << __FILE__ << ", Ligne:" << __LINE__ << std::endl;

    #undef GAME_RELEASE

    #ifdef GAME_RELEASE
        std::cout << "GAME RELEASE" << endl;
    #else
        std::cout << "GAME DEBUG" << endl;
    #endif

    #ifndef STEAM_VERSION
            std::cout << "N'est pas sur Steam" << endl;  
    #endif
}
