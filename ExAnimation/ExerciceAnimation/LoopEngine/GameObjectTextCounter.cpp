#include "GameObjectText.h"
#include "GameObjectTextCounter.h"

LE::GameObjectTextCounter::GameObjectTextCounter(int InX, int InY)
    :GameObjectText(InX, InY, "X", 32)
{
    _Timer.SetDuration(1.f);
    _Timer.SetActive(true);
    _Timer.PlayOnce(false);
    ////////////////////////////////////
    //3) Faite que le texte par d�faut soit 0 et non X

    ////////////////////////////////////
    _Timer.SetCallback(
        [this]() {
            ////////////////////////////////////
            //4) Faite qu'� chaque fois que le timer d�passe sa dur�e,
            //Il incr�mente la valeur du compteur � et met � jour le texte.
            //Vous ne verrez aucun changement � ce stade, compl�tez 5) avant!

            ////////////////////////////////////
        }
    );
}

LE::GameObjectTextCounter::~GameObjectTextCounter()
{}

void LE::GameObjectTextCounter::SetActive(bool InIsActive)
{
    _Timer.SetActive(InIsActive);
}

void LE::GameObjectTextCounter::Reset()
{
    _Timer.Reset();
}

void LE::GameObjectTextCounter::SetDuration(float InDuration)
{
    _Timer.SetDuration(InDuration);
}

void LE::GameObjectTextCounter::PreUpdate()
{
    ////////////////////////////////////
    //5) Mettez � jour le timer avec Uppdate. On doit passer la dur�e du frame et non le temps absolu.
    //Le compteur devrait fonctionner maintenant! Retournez dans main.cpp

    ////////////////////////////////////
}