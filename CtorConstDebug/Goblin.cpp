#include "Goblin.h"
#include <iostream>

using namespace std;

Goblin::Goblin()
//Pr�constructeur
//1) Pour appeler un autre constructeur avec des param�tres
	:Goblin::Goblin("NoName")
{
	cout << "Goblin::Goblin() est appel�. " << "("<< _Name << ")" << endl;
}

Goblin::Goblin(const string& InName)
//Pr�constructeur
//2) Pour initialiser une const
//3) Pour initialiser des valeurs (bonne pratique mais pas obligatoire)
	:_Name(InName),
	_Life(20)
{
	cout << "Goblin::Goblin(const string& InName) est appel�. " << "(" << _Name << ")" << endl;
}

Goblin::~Goblin()
{
	cout << "Goblin::~Goblin() est appel�. " << "(" << _Name << ")" << endl;
}

const string& Goblin::GetName() const
{
	//Interdit � cause que Goblin::GetName() const
	//_Name = "GlobinCoquin";
	return _Name;
}

int Goblin::GetLife() const
{

	//Interdit � cause que GetLife() const
	//_Life = 10;
	return _Life;
}

void Goblin::SetLife(int InLife)
{
	//Modification permise car aucun const
	_Life = InLife;
}
