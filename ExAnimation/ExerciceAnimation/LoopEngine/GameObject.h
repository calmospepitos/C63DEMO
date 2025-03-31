#pragma once
#include <functional>
#include <memory>
#include <string>
#include "raylib.h"
#include "BaseObject.h"

//Banque d'objets de jeu g�n�rique

namespace LE
{
	////////////////////////////////////////
	/// 2D objects
	////////////////////////////////////////
	class GameObject2D;
	//Informations de collision lorsque 2 objets se touches.
	struct CollisionEvent
	{
		Vector2 _Position;
		GameObject2D const * _MyObject;
		GameObject2D const * _OtherObject;
	};

	//Object g�n�rique avec une position 2D. Peut collisionner avec d'autres objets.
	//Peut optionnellement avoir un nom.
	class GameObject2D : public IBaseObject, public std::enable_shared_from_this<GameObject2D>
	{
	protected:
		Rectangle _CollisionBox = Rectangle{0.f,0.f,100.f,100.f};
		int _CollisionMaks = 0;
		std::string _Name = "Nameless";
		std::function<void(const CollisionEvent&)> _CallbackOnCollision = nullptr;

	public:
		GameObject2D(const std::string& InName = "GameObject2D");
		//Log WARNING: Objet nomm� X a une boite de collision invalide (valeur n�gative). Collision d�sactiv�e (collision mask = 0).
		//Log WARNING: Un objet a un nom vide!
		GameObject2D(Vector2 InPosition, Vector2 InCollisionBox, int InCollisionMask, const std::string& InName = "GameObject2D");
		virtual ~GameObject2D();

		void SetCollisionMask(int InCollisionGroup);
		int GetCollisionMask() const;

		void SetPosition(Vector2 InPosition);
		const Vector2& GetPosition() const;

		//Log WARNING: Un objet a un nom vide!
		void SetName(const std::string& InName);
		const std::string& GetName() const;

		//Log WARNING: Objet nomm� X a une boite de collision invalide (valeur n�gative). La boite n'est pas modifie.
		void  SetCollisionBox(const Vector2& InNewBoxSize);
		//Retourne la grosseur x et y de la boite de collision
		const Vector2& GetCollisionBox() const;
		//Retourne un rectangle plac� � la position de l'objet et de la grosseur de la bo�te de collision
		virtual const Rectangle& GetCollisionAtPosition() const;

		//*=*=*=*=*=*=*=*AVANC�=*=*=*=*=*=*=*=*=//
		//Dans la classe Scene, dans le PreUpdate, apr�s avoir appel� PreUpdate sur les objets de jeu, on test les collisions entre tous les objets
		//de jeu, un peu comme dans l'exercice. Comme r�gle suppl�mentaire, on a les masques de collision comme expliqu� plus haut.
		virtual void OnCollisionEvent(std::function<void(const CollisionEvent&)> InFunctionToCall);
		virtual bool CheckCollision(const std::weak_ptr<GameObject2D> InOtherGO, bool InNotify = false);
		//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=//

		//======D�BUT======
		//GameObject2D ne fait rien ici, mais �a fourni un interface pour les classes qui en h�ritent
		//Vous n'avez rien � faire
		virtual void Load() {}
		virtual void Unload() {}

		virtual void PreUpdate() {}
		virtual void Draw3D() {}
		virtual void Draw2D() {}
		virtual void DrawDebug() {}
		virtual void LateUpdate() {}
		//======FIN======

		virtual void Destroy();
	};

	//Affiche une image � la position et le scale donn�.
	class GameObjectSingleImage : public GameObject2D
	{
		protected:
			Image _Image;
			Texture _Texture;
			Color _Tint = WHITE;
			float _Rotation = 0.0f;
			float _Scale = 1.0f;
			std::string _FilePathToLoad;
			bool _IsLoaded = false;

		public:
			//Log ERROR: Objet nomm� X a un nom de fichier vide.
			//Log WARNING: Objet nomm� X r�f�re un fichier non-existant. Note: Il existe une fonction pour v�rifier si un fichier existe dans Raylib!
			//Chemin valide pour acc�der au fichier dans {racineVSProjet}/res/Test-Image.png:
			//string(GetWorkingDirectory()) + "\\res\\Test-Image.png"
			GameObjectSingleImage(const std::string& InImageFileName,const std::string& InName = "GameObjectSingleImage");
			//Attention, il faut v�rifier si Image et Texture sont encore charg�s!
			virtual ~GameObjectSingleImage();

			void SetScale(float InScale);
			float GetScale() const;

			void SetRotation(float InRotationInDegree);
			float GetRotation() const;

			void SetColorTint(const Color& InColorTint);
			const Color& GetColorTint() const;

			virtual const Rectangle& GetCollisionAtPosition() const;

			//L'Image et la Texture sont charg�es au moment du load.
			//Log WARNING: Objet nomm� X r�f�re un fichier non-existant. Note: Il existe une fonction pour v�rifier si un fichier existe dans Raylib!
			//Log WARNING: Objet nomm� X a d�j� charg� son image et ne peut la recharger.
			virtual void Load();
			//L'Image et la Texture sont d�charg�es au moment du unload.
			//Log WARNING: Objet nomm� X n'a pas d'image charg� et ne peut la d�charger.
			virtual void Unload();

			//Returne l'objet Image
			const Image& GetImage() const;
			//Returne l'objet Texture
			const Texture& GetTexture() const;
			//Affiche la Texture � la position et la grosseur fournie
			//Si l'image n'est pas charg�, on affiche un carr� de la couleur tent�e (ColorTint) de la grosseur de la boite de collision
			virtual void Draw2D() override;

			//Note: les autres m�thodes fournies par le parent (PreUpdate,Draw3D et LateUpdate) n'ont pas besoin d'�tre cod�e ici
			//car on en a pas besoin!
	};

class GameObjectTile : public GameObjectSingleImage
{
	protected:
		float _TextureScale = 1.0f;

	public:
		GameObjectTile(const std::string& InImageFileName, const Rectangle& InSceneRectangle);
		virtual void Draw2D() override;
};
}

