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
		_Position = Vector2Zero(); // On initialise la position à 0
		const auto ptrLower = InLowerIndexFlee.lock(); // On crée un pointeur de la puce avec le plus petit index
		const auto ptrHigher = InHigherIndexFlee.lock(); // On crée un pointeur de la puce avec le plus grand index
		if (ptrLower && ptrHigher) // Si les deux puces existent
        {
			_Position = Vector2Scale(Vector2Add(ptrHigher->GetPosition(), ptrLower->GetPosition()), 0.5f); // On calcule la position de l'évènement de collision
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

    // 1) Créer une structure de donnée pour contenir des smart pointeur de puce sans la remplir
	vector<shared_ptr<Flee>> flees; // Les vecteurs sont des tableaux dynamiques en c++, donc un tableau sans taille fixe
	flees.reserve(nbFlee); // On réserve de la mémoire pour les puces

    // 2) Dans une boucle, créez des puces et placez-les au hasard à l'intérieur de border min et border max
    // Indice: regardez la fonction raylib GetRandomValue
    // Soyez explicite si des données changes de type.
	for (int i = 0; i < nbFlee; i++) // On crée une boucle pour créer plusieurs puces
    {
		float randomX = (float)GetRandomValue((int)borderMin.x, (int)borderMax.x);
		float randomY = (float)GetRandomValue((int)borderMin.y, (int)borderMax.y);
		Vector2 randomPosition = { randomX, randomY }; // On crée un vecteur 2D des coordonnées de la puce avec les valeurs randomX et randomY
		shared_ptr<Flee> flee = make_shared<Flee>(randomPosition, 100.0f, borderMin, borderMax); // On crée une puce avec les valeurs randomPosition, velocite de 100.0f, borderMin et borderMax
		flees.push_back(flee); // push_back() = on ajoute la puce au vecteur de puces
    }

    // 3) Allez voir plus haut ce que fait la structure et prenez le temps de la comprendre. Initializé toutes les valeurs de la struct.
    // Pour l'attribut _Position, prenez la position de la puce avec le plus petit index (InLowerIndexFlee)
    // SAVIEZ_VOUS? En c++, struct et classe sont très similaires et on peut mettre des méthodes (incluant des constructeurs/destructeurs) aux struct

    // 4) Créer une structure de données pour contenir des smart pointer d'évènement de collision.
    vector<shared_ptr<CollisionEvent>> collisionEvent; // On crée un vecteur de smart pointer d'évènement de collision
    collisionEvent.reserve(20000); // On réserve de la mémoire pour les évènements de collision

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
            // 5) Dans raylib, trouvez uen manière de dessiner le nombre d'images par secondes en haut à gauche, communément abrévié FPS en anglais
			DrawFPS(10, 10); // On affiche le nombre d'images par seconde en haut à gauche

            // 6) En haut dans le milieu, écrivez le nombre total de puces en noir
			DrawText(TextFormat("%2i total flees", flees.size()), 100, 10, 24, BLACK); // On affiche le nombre de puces en haut à gauche, %2i = 2 chiffres

            // 7) En haut à droite, écrivez le nombre total de collisions
			DrawText(TextFormat("%2i total collision", collisionEvent.size()), 300, 10, 24, BLACK); // On affiche le nombre de collisions en haut à droite

            // 8) Pour chaque puce, faites-la avancer (méthode Move) et dessinez-la (méthode Draw).
            for (int i = 0; i < flees.size(); i++) // On crée une boucle pour chaque puce
            {
				flees[i]->Move(deltaTime); // On fait avancer la puce, deltaTime = temps entre chaque frame
				flees[i]->Draw(); // On dessine la puce
                for (int j = i + 1; j < flees.size(); j++) // On crée une boucle pour chaque puce
                {
					if (flees[i]->CollideWith(flees[j])) // Si les puces i et j entrent en collision
					{
						shared_ptr<CollisionEvent> event = make_shared<CollisionEvent>(flees[i], flees[j], totalTime); // On crée un évènement de collision
						collisionEvent.push_back(event); // On ajoute l'évènement de collision au vecteur d'évènements de collision
					}
                }
            }

            // 9) À l'intérieur de la boucle précédente, trouvez une solution pour tester la collision (méthode CollideWith) entre toutes les paires de puces possible
            // Chaque paire devrait être testée une seule fois! Si une collision est détectée, créez et ajoutez un évènement de collision.
            
            // 11) Dans une nouvelle boucle, pour chaque évènement de collision...
            // 11.1) Dessinez un carré blanc transparent de 5 par 5 à chaque position qu'il y a eu une collision
            Color transparentWhite = Color{ 255, 255, 255, 25 }; // White with 10% opacity

			for (const auto& event : collisionEvent) // On crée une boucle pour chaque évènement de collision
            {
				if (auto ptr = event) // Si l'évènement existe
                {
					DrawRectangle(ptr->_Position.x - 2, ptr->_Position.y - 2, 5, 5, transparentWhite); // On dessine un carré blanc transparent de 5 par 5 à la position de l'évènement

					auto ptrLower = ptr->_LowerIndexFlee.lock(); // On crée un pointeur de la puce avec le plus petit index
					auto ptrHigher = ptr->_HigherIndexFlee.lock(); // On crée un pointeur de la puce avec le plus grand index

                    if (ptrLower && ptrHigher) // Si les deux puces existent
                    {
						Vector2 lowerPosition = ptrLower->GetPosition(); // On récupère la position de la puce avec le plus petit index
						Vector2 higherPosition = ptrHigher->GetPosition(); // On récupère la position de la puce avec le plus grand index
						DrawLine(lowerPosition.x, lowerPosition.y, higherPosition.x, higherPosition.y, Color{ 0, 0, 0, 25 }); // On dessine une ligne entre les deux puces
                    }
                }
            }

            // 11.2) Dessinez une ligne noire transparente entre chaque puce qui a subit une collision
            // Suggestion de couleur: Color{ 25, 25, 25, 25 } et Color{ 255, 255, 255, 25 }

            // 12) À chaque dois qu'on pèse sur espace, une puce doit être supprimez. Votre programme ne devrait pas crasher si vous l'avez fait correctement!
            if (IsKeyPressed(KEY_SPACE) && !flees.empty()) // If spacebar is pressed and there's at least one flea
            {
                flees.pop_back(); // Remove the last flea in the vector
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}