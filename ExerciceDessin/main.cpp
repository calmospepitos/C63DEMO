// ExerciceDessin.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include <iostream>
#include <raylib.h>

// VARIABLES
typedef enum GameScreen { PACMAN, CHARGEMENT } GameScreen;

int main()
{
    // Initialization
     //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Exercice Pacman");

    GameScreen currentScreen = PACMAN;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0;          // Useful to count frames

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        switch (currentScreen)
        {
            case PACMAN:
            {
                framesCounter++;

                if (IsKeyPressed(KEY_SPACE))
                {
                    currentScreen = CHARGEMENT;
                }
            } break;
            case CHARGEMENT:
            {
                framesCounter++;

                if (IsKeyPressed(KEY_SPACE))
                {
                    currentScreen = PACMAN;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case PACMAN:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);

            // Draw Pac-Man shape
            Vector2 center = { screenWidth / 4.0f, screenHeight / 2.0f };
            float radius = 75.0f;
            float startAngle = 35.0f;
            float endAngle = 335.0f;
            int segments = 0; // Use default number of segments

            DrawCircleSector(center, radius, startAngle, endAngle, segments, YELLOW);

            // Draw text
            const char* text = "Waka waka!";
            int fontSize = 40;
            int textWidth = MeasureText(text, fontSize);
            int textX = center.x - textWidth / 4.0f;
            int textY = center.y + radius + 10; // 10 pixels below the Pac-Man shape

            DrawText(text, textX, textY, fontSize, WHITE);

			// Draw Pac-Dots
			float pacDotRadius = 30.0f;
			float separation = 40.0f;
			float startX = center.x + radius + 100.0f;

			for (int i = 0; i < 3; i++)
            {
                DrawCircle(startX + i * (pacDotRadius * 2 + separation), center.y, pacDotRadius, LIGHTGRAY);
			}

        } break;
        case CHARGEMENT:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, VIOLET);

            // Draw patterned wallpaper
            int shapeSize = 20; // Size of each shape
            int separation = 60; // Separation between shapes
            int totalRows = 9; // Total number of rows
            int cols = screenWidth / (shapeSize + separation); // Number of columns in the pattern
            int rowHeight = screenHeight / totalRows; // Height of each row

            for (int i = 0; i < totalRows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    int x = j * (shapeSize + separation);
                    int y = i * rowHeight;

                    if (i % 3 == 0)
                    {
                        // First row: small circles
                        DrawCircle(x + separation / 2, y + rowHeight / 2, shapeSize / 2, PURPLE);
                    }
                    else if (i % 3 == 1)
                    {
                        // Second row: small squares
                        DrawRectangle(x + separation / 2, y + rowHeight / 2 - shapeSize / 2, shapeSize, shapeSize, PURPLE);
                    }
                    else if (i % 3 == 2)
                    {
                        // Third row: exclamation marks
                        DrawText("!", x + separation / 2, y + rowHeight / 2 - shapeSize / 2, shapeSize, PURPLE);
                    }
                }
            }

            // Draw centered text "loading..."
            const char* loadingText = "Loading...";
            int fontSize = 80;
            int textWidth = MeasureText(loadingText, fontSize);
            int textX = (screenWidth - textWidth) / 2;
            int textY = (screenHeight - fontSize) / 2;

            DrawText(loadingText, textX, textY, fontSize, GOLD);
        } break;
        default: break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // TODO: Unload all loaded data (textures, fonts, audio) here!
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
