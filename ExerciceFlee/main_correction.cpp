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
        _Position = Vector2Zero();
        const auto ptrLower = InLowerIndexFlee.lock();
        const auto ptrHigher = InHigherIndexFlee.lock();
        if (ptrLower && ptrHigher)
        {
            _Position = Vector2Scale(Vector2Add(ptrHigher->GetPosition(), ptrLower->GetPosition()), 0.5f);
        }
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
    vector<shared_ptr<Flee>> allFlees;
    allFlees.reserve(10);

    //2) Dans une boucle, créez des puces et placez-les au hasard à l'intérieur de border min et border max
    //Indice: regardez la fonction raylib  GetRandomValue
    //Soyez explicite si des données changes de type.
    for (int i = 0; i < nbFlee; ++i)
    {
        float randomX = static_cast<float>(GetRandomValue(borderMin.x, borderMax.x));
        float randomY = static_cast<float>(GetRandomValue(borderMin.y, borderMax.y));
        allFlees.push_back(make_shared<Flee>(Vector2{ randomX, randomY },500.f, borderMin, borderMax));
    }

    //3) Allez voir plus haut ce que fait la structure et prenez le temps de la comprendre. Initializé toutes les valeurs de la struct.
    //Pour l'attribut _Position, prenez la position de la puce avec le plus petit index (InLowerIndexFlee)
    //?SAVIEZ_VOUS? En c++, struct et classe sont très similaires et on peut mettre des méthodes (incluant des constructeurs/destructeurs)
    //aux struct
    
    //4) Créer une structure de données pour contenir des smart pointer d'évènement de collision.
    vector<shared_ptr<CollisionEvent>> collisionEvent;
    collisionEvent.reserve(20000);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE) && !allFlees.empty())
        {
            allFlees.pop_back();
        }

        const float deltaTime = GetFrameTime();
        const float time = GetTime();
            BeginDrawing();
                ClearBackground(BLUE);
                DrawLine(borderMin.x, borderMin.y, borderMin.x, borderMax.y, PURPLE);
                DrawLine(borderMin.x, borderMin.y, borderMax.x, borderMin.y, PURPLE);
                DrawLine(borderMax.x, borderMin.y, borderMax.x, borderMax.y, PURPLE);
                DrawLine(borderMin.x, borderMax.y, borderMax.x, borderMax.y, PURPLE);
                //5) Dans raylib, trouvez uen manière de dessiner le nombre d'images par secondes en haut à gauche, communément abrévié FPS en anglais
                DrawFPS(10, 10);
                //6) En haut dans le milieu, écrivez le nombre total de puces en noir
                DrawText(TextFormat("%2i total flees", allFlees.size()), 100, 10, 24, BLACK);
                //7) En haut à droite, écrivez le nombre total de collisions
                DrawText(TextFormat("%2i total collision", collisionEvent.size()), 300, 10, 24, BLACK);

                //8)Pour chaque puce, faites-la avancer (méthode Move) et dessinez-la (méthode Draw).
                for (int i = 0; i < allFlees.size(); ++i)
                {
                    allFlees[i]->Move(deltaTime);
                    allFlees[i]->Draw();
                    for (int j = i+1; j < allFlees.size(); ++j)
                    {
                        if (allFlees[i]->CollideWith(allFlees[j]))
                        {
                            collisionEvent.push_back(make_shared<CollisionEvent>(allFlees[i], allFlees[j], time));
                        }
                    }
                }

                //9) À l'intérieur de la boucle précédente, trouvez une solution pour tester la collision (méthode CollideWith) entre toutes les paires de puces possible
                //Chaque paire devrait être testée une seule fois! Si une collision est détectée, créez et ajoutez un évènement de collision.

                //11) Dans une nouvelle boucle, pour chaque évènement de collision...
                //11.1) Dessinez un carré blanc transparent de 5 par 5 à chaque position qu'il y a eu une collision
                //11.2) Dessinez une ligne noire transparente entre chaque puce qui a subit une collision
                //Suggestion de couleur: Color{ 255, 255, 255, 25 }
                for (auto it_ev = collisionEvent.begin(); it_ev != collisionEvent.end(); ++it_ev)
                {
                    DrawRectangle(it_ev->get()->_Position.x, it_ev->get()->_Position.y, 5, 5, Color{ 255, 255, 255, 25 });
                    if (const auto ptrLower = it_ev->get()->_LowerIndexFlee.lock())
                    {
                        if (const auto ptrHigher = it_ev->get()->_HigherIndexFlee.lock())
                        {
                            DrawLine(ptrLower->GetPosition().x, ptrLower->GetPosition().y, ptrHigher->GetPosition().x, ptrHigher->GetPosition().y, Color{ 0, 0, 0, 25 });
                        }
                    }
                }

                //12) À chaque dois qu'on pèse sur espace, une puce doit être supprimez. Votre programme ne devrait pas crasher si vous l'avez fait correctement!

            EndDrawing();
    }

    CloseWindow();
    return 0;
}