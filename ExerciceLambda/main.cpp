// ExerciceDessin.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <raylib.h>
#include "Button.h"

// VARIABLES
Color backgroundColor = RAYWHITE;

void ButtonAction1() { backgroundColor = BLUE; }
void ButtonAction2() { std::cout << "Bonjour, Raylib!" << std::endl; }
void ButtonAction3() { CloseWindow(); exit(0); }

int main()
{
    // Initialization
     //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    // Define button size
    const int buttonWidth = 200;
    const int buttonHeight = 50;

    // Calculate centered X position
    const int centerX = (screenWidth - buttonWidth) / 2;

    InitWindow(screenWidth, screenHeight, "Exercice Lambda");

    // TODO: Initialize all required variables and load all required data here!
    int framesCounter = 0;          // Useful to count frames

    // Create buttons centered horizontally
    Button bouton1(centerX, 200, buttonWidth, buttonHeight, "Action 1", ButtonAction1);
    Button bouton2(centerX, 350, buttonWidth, buttonHeight, "Action 2", ButtonAction2);
    Button bouton3(centerX, 500, buttonWidth, buttonHeight, "Action 3", ButtonAction3);

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

		// Background
        ClearBackground(backgroundColor);

		// Boutons
        bouton1.DrawAndUpdate();
        bouton2.DrawAndUpdate();
        bouton3.DrawAndUpdate();
        
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // TODO: Unload all loaded data (textures, fonts, audio) here!
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
