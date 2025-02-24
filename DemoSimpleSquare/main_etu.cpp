#include <iostream>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "SimpleSquare.hpp"

//À inclure pour l'utilisation des pointeurs automatiques
#include <memory> // Ça inclut des smart pointers

int main(void)
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 800;
    constexpr float buffer = 80.f;
    constexpr float delta = 100.f;

    InitWindow(screenWidth, screenHeight, "Demo pointeurs automatiques");

    Vector2 currentDrawPosition = Vector2{ buffer,buffer };
    Vector2 drawPositionDelta = Vector2{ delta,delta };

    //Objet automatique
    SimpleSquare hautGauche(currentDrawPosition,"Objet automatique",GREEN);

    //Pointeur normal - ne pas oublier de supprimer!
    currentDrawPosition = Vector2Add(currentDrawPosition, drawPositionDelta);
    SimpleSquare* ptrSimpleSquare = new SimpleSquare(currentDrawPosition, "Pointeur classique", YELLOW);

    //Pointeur partagé
    currentDrawPosition = Vector2Add(currentDrawPosition, drawPositionDelta);
    std::shared_ptr<SimpleSquare> ptrSharedSimpleSquare = std::make_shared<SimpleSquare>(currentDrawPosition, "Pointeur partage", WHITE);
    std::shared_ptr<SimpleSquare> ptrSharedSimpleSquareCopy = ptrSharedSimpleSquare; // use_count() ++

    {
        std::shared_ptr<SimpleSquare> ptrSharedSimpleSquareCopyCopy = ptrSharedSimpleSquare; // use_count() ++
        // ptrSharedSimpleSquareCopyCopy ne peux plus être utilisé après la portée, donc use_count() --
    }

    //Pointeur faible
    currentDrawPosition = Vector2Add(currentDrawPosition, drawPositionDelta);
    std::weak_ptr<SimpleSquare> ptrWeakSimpleSquare = ptrSharedSimpleSquare; // make_weak n'existe pas
    // Un weak pointer n'augmente pas use_count()

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(VIOLET);
            hautGauche.Draw();

            if (ptrSimpleSquare != nullptr) {
                (*ptrSimpleSquare).Draw();
                // Identique à ptrSimpleSquare()->Draw();
            }

            if (ptrSharedSimpleSquare != nullptr) {
                ptrSharedSimpleSquare->Draw(std::to_string(ptrSharedSimpleSquare.use_count()));
            }

            if (auto tempShared = ptrWeakSimpleSquare.lock()) {
                tempShared->Draw(std::to_string(ptrSharedSimpleSquare.use_count()));
            }

        EndDrawing();
    }

    CloseWindow();

    if (ptrSimpleSquare != nullptr) {
        delete ptrSimpleSquare;
    }

    return 0;
}