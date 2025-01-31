#include <iostream>
#include <windows.h> //Pour SetConsoleOutputCP
#include "Goblin.h"

//D�claration de fonctions globales pour tant�t
void PresentationGoblinTresMalFait(Goblin InGoblin);
void PresentationGoblinMalFait(Goblin InGoblin);
void PresentationGoblinBienFait(Goblin InGoblin);

int main()
{
    //Pour voir les accents comme il faut.
    SetConsoleOutputCP(1252);

    cout << endl << "Dur�e de vie d'un objet automatique" << endl;
    {
        //Construit ici
        Goblin goblinAutomatique;
    } //D�truit ici

    cout << endl << "Dur�e de vie d'un objet automatique: dans un if" << endl;
    if (true)
    {
        //Construit ici
        Goblin goblinAutomatiqueDansUnIf("IffyGoblin");
    } //D�truit ici


    cout << endl << "Dur�e de vie d'un objet cr�� avec new" << endl;
    //Construit ici
    Goblin* ptrGoblin = new Goblin("PeterLeGoblin");
    const string& nomDeptrGoblin = ptrGoblin->GetName();
    cout << "Je suis " << nomDeptrGoblin << endl;
    //D�truit ici
    delete ptrGoblin;
    ptrGoblin = nullptr;

    cout << endl << "Passage par param�tre" << endl;

    Goblin goblinPresentateur("GoblinPresentateur");
    PresentationGoblinTresMalFait(goblinPresentateur);
    cout << endl;
    PresentationGoblinMalFait(goblinPresentateur);
    cout << endl;
    PresentationGoblinBienFait(goblinPresentateur);

}


//Impl�mentation
void PresentationGoblinTresMalFait(Goblin InGoblin)
{
    cout << "Pr�sentation tr�s mal faite du goblin " << InGoblin.GetName() << endl;
}

void PresentationGoblinMalFait(const Goblin InGoblin)
{
    cout << "Pr�sentation mal faite du goblin " << InGoblin.GetName() << endl;
}

void PresentationGoblinBienFait(const Goblin InGoblin)
{
    cout << "Pr�sentation bien fait du goblin " << InGoblin.GetName() << endl;
}
