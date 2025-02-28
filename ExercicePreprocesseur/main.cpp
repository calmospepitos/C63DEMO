// ExerciceDessin.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <raylib.h>
#include "custommacro.h"

using namespace std;

int main()
{
    cout << "NATURAL_NUMBER: " << NATURAL_NUMBER << endl;
    cout << "FIBONNACCI_NUMBER: " << FIBONNACCI_NUMBER << endl;
    cout << "WIERD_NUMBER: " << WIERD_NUMBER << endl;

    float result1 = 2.0f * NATURAL_NUMBER + WIERD_NUMBER;
    float result2 = 2.0f * WIERD_NUMBER;

    LOG("2.0f * NATURAL_NUMBER + WIERD_NUMBER: " << result1);
    LOG("2.0f * WIERD_NUMBER: " << result2);

    return 0;
}
