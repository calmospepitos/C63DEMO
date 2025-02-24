#include "raylib.h"
#include "raymath.h"
#include "Flee.h"
#include <iostream>
#include <memory>
#include <vector>
#include <set>

using namespace std;


struct CollisionEvent
{
    weak_ptr<Flee> _LowerIndexFlee;
    weak_ptr<Flee> _HigherIndexFlee;
    Vector2 _Position;
    float _TimeOfImpact;

    CollisionEvent(weak_ptr<Flee> InLowerIndexFlee, weak_ptr<Flee> InHigherIndexFlee, float InTimeOfImpact)
        : _LowerIndexFlee(InLowerIndexFlee)
        , _HigherIndexFlee(InHigherIndexFlee)
        , _TimeOfImpact(InTimeOfImpact)
    {
        //Constructeur ici
    }
};

int main(void)
{
    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 1000;
    constexpr int borderMargin = 50;
    constexpr int nbFlee = 25;

    constexpr Vector2 borderMin = Vector2{ borderMargin ,borderMargin };
    constexpr Vector2 borderMax = Vector2{ screenWidth - borderMargin , screenHeight - borderMargin };
    InitWindow(screenWidth, screenHeight, "Flee bonanza!");

    //1) Créer une structure de donnée pour contenir des smart pointeur de puce sans la remplir


    //2) Dans une boucle, créez des puces et placez-les au hasard à l'intérieur de border min et border max
    //Indice: regardez la fonction raylib  GetRandomValue
    //Soyez explicite si des données changes de type.


    //3) Allez voir plus haut ce que fait la structure et prenez le temps de la comprendre. Initializé toutes les valeurs de la struct.
    //Pour l'attribut _Position, prenez la position de la puce avec le plus petit index (InLowerIndexFlee)
    //?SAVIEZ_VOUS? En c++, struct et classe sont très similaires et on peut mettre des méthodes (incluant des constructeurs/destructeurs)
    //aux struct
    

    //4) Créer une structure de données pour contenir des smart pointer d'évènement de collision.


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        const float deltaTime = GetFrameTime();
        const float totalTime = GetTime();
        BeginDrawing();
            ClearBackground(BLUE);
            DrawLine(borderMin.x, borderMin.y, borderMin.x, borderMax.y, PURPLE);
            DrawLine(borderMin.x, borderMin.y, borderMax.x, borderMin.y, PURPLE);
            DrawLine(borderMax.x, borderMin.y, borderMax.x, borderMax.y, PURPLE);
            DrawLine(borderMin.x, borderMax.y, borderMax.x, borderMax.y, PURPLE);
            //5) Dans raylib, trouvez uen manière de dessiner le nombre d'images par secondes en haut à gauche, communément abrévié FPS en anglais

            //6) En haut dans le milieu, écrivez le nombre total de puces en noir

            //7) En haut à droite, écrivez le nombre total de collisions

            //8)Pour chaque puce, faites-la avancer (méthode Move) et dessinez-la (méthode Draw).

            //9) À l'intérieur de la boucle précédente, trouvez une solution pour tester la collision (méthode CollideWith) entre toutes les paires de puces possible
            //Chaque paire devrait être testée une seule fois! Si une collision est détectée, créez et ajoutez un évènement de collision.

            //11) Dans une nouvelle boucle, pour chaque évènement de collision...
            //11.1) Dessinez un carré blanc transparent de 5 par 5 à chaque position qu'il y a eu une collision
            //11.2) Dessinez une ligne noire transparente entre chaque puce qui a subit une collision
            //Suggestion de couleur: Color{ 25, 25, 25, 25 } et Color{ 255, 255, 255, 25 }


            //12) À chaque dois qu'on pèse sur espace, une puce doit être supprimez. Votre programme ne devrait pas crasher si vous l'avez fait correctement!

        EndDrawing();
    }

    CloseWindow();
    return 0;
}