#pragma onc
#include <string>

using namespace std;

class Goblin
{
public:
	//Constructeur - toujours appel� automatiquement lors de la construction.
	Goblin();
	//Overload du constructeur possible
	//TOUJOURS: Passer un const & pour toutes les non primitives
	//Si on passe string ou const string, la string sera copi�e.
	Goblin(const string& InName);
	//Destructeur - toujours appel� lors de la destruction.
	~Goblin();


	//const string&: retourne une R�F�RENCE (et non une copie) de la string. La string ne peut pas �tre modifi�e
	// gr�ce au const. Autrement, �a reviendrait � modifier la string de l'instance de l'ext�rieur ce qui n'est
	//pas id�al
	//GetName() const: L'instance courrante (le this) n'est pas modifi�.
	const string&  GetName() const;


	//GetLife() const: L'instance courrante (le this) n'est pas modifi�.
	int GetLife() const;
	//Ici, on modifie le membre _Life donc on ne peut pas faire void SetLife(int InLife) const;
	void SetLife(int InLife);

private:
	//Une constante initialis�e dans la d�claration de classe.
	const string _Name = "GoblinNoName";
	int _Life = 10;
};

