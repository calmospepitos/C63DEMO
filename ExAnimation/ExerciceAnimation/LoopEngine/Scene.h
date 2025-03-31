#pragma once
#include <string>
#include <memory>
#include <vector>
#include "BaseObject.h"
#include "GameObject.h"

namespace LE
{
	class Scene : public IBaseObject
	{
		private:
			//Ici vous devez avoir une collection de GameObject2D ainsi que le nom de la sc�ne.
			std::vector<std::shared_ptr<GameObject2D>> _GO2D;
			const std::string _Name = "NoName";

		public:
			//Log ERROR: Nom de sc�ne vide.
			Scene(const std::string& InName);
			virtual ~Scene();

			//Retourne le nom de la sc�ne.
			const std::string& GetName() const;

			//Ajoute un GameObject2D de la collection
			//Si la sc�ne est active, on appel Load sur l'objet ajout�
			//Log WARNING: Objet nomm� X d�j� dans la sc�ne, l'objet n'est pas ajout�.
			void AddGameObject2D(std::shared_ptr<GameObject2D> InNewGameObject);

			//Enl�ve un GameObject2D
			//Si la sc�ne est active, on appel Unload sur l'objet ajout�
			//Log WARNING: Objet nomm� X n'est pas dans dans la sc�ne, l'objet n'est pas enlev�.
			void RemoveGameObject2D(std::shared_ptr<GameObject2D> InRemovedGameObject);
			bool HasGameObject2D(std::shared_ptr<GameObject2D> InGameObject);

			//Appel Load sur les GameObject2D
			//Log WARNING: Sc�ne d�j� load�, la sc�ne ne reloadera pas.
			void Load();
			//Appel Unload sur les GameObject2D
			//Log WARNING: Sc�ne n'est pas load�e, la sc�ne ne d�loadera pas.
			virtual void Unload();

			//Les m�thodes suivantes sont appel�es dans l'ordre dans le while � chaque image affich�e.
			//Effectue les test de collisions, puis appelle PreUpdate sur les GameObject2D
			virtual void PreUpdate();
			//Appel Draw3D sur les GameObject2D
			virtual void Draw3D();
			//Appel Draw2D sur les GameObject2D
			virtual void Draw2D();
			virtual void DrawDebug();
			//Compare tous les objets entre eux pour voir s'ils collisionnent et appel le fonction de callback au besoin
			//Filtre selon les masque de collision
			virtual void CheckAndNotifyCollision();
			//Appel LateUpdate sur les GameObject2D
			virtual void LateUpdate();
	};
}