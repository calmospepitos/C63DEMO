#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>
#include "raylib.h"
#include "ServiceLocator.h"
#include "Scene.h"

using namespace std;

namespace LE
{
	class Engine;
	class IEngineService : public IService
	{
	public:
		virtual void SendLateUpdateCommand(function<void(LE::Engine&)> InNewCommand) = 0;

		virtual void SetClearColor(Color InColor) = 0;
		virtual const Color& GetClearColor() const = 0;
		virtual void SetDebugMode(bool InDebugMode) = 0;
		virtual bool GetDebugMode() const = 0;
		virtual bool IsSceneRegistered(const string& InNewSceneName) const = 0;
	};

	//Fonction globale pour envoyer des commandes a Engine via le Service Locator
	//C'est juste un raccourcis au lieu de directement passer par le Service Locator
	extern void SendCommand(function<void(LE::Engine&)> InNewCommand);

	class Engine : public ServiceBase<IEngineService>
	{
	protected:
		map<string, shared_ptr<LE::Scene>> _NameToScene;
		weak_ptr<LE::Scene> _ActiveScene;
		Color _ClearColor = BLACK;
		int _ResolutionX = 800;
		int _ResolutionY = 800;
		int _FPS = 60;
		string _Title = "Sans titre";

		bool _DebugMode = false;
		bool _RequestClose = false;

		vector<function<void(LE::Engine&)>> _EngineCommandList;
	
	public:
		//Log INFO: � la fin du constructeur, signaler que Engine est construit.
		//Log ERROR: Resolution n�gative, TargetFPS en dehors de [5,100].
		Engine(int InResolutionX = 800, int InResolutionY = 480, const string& InTitle = "Sans titre", int InTargetFPS = 60);
		virtual ~Engine();

		//Appeler cette m�thode pour ouvrir la fen�tre et d�marrer la boucle while
		//Log INFO: Signaler que le jeu a d�marr� avec la sc�ne InStartSceneName
		//Log ERROR: Sc�ne de d�marrage n'existe pas.
		//Log ERROR: Aucune sc�ne enregistr�e.
		void StartGame(const string& InStartSceneName);

		//Couleur de fond de l'application
		void SetClearColor(Color InColor);
		const Color& GetClearColor() const;

		//Si � vrai, va afficher le FPS en haut � droite et le message suivant: "Press P to toggle debug"
		//Codez aussi que si l'usager appuie sur la touche p, le mode debug change de vrai � faux ou l'inverse
		void SetDebugMode(bool InDebugMode);
		bool GetDebugMode() const;

		//*=*=*=*=*=*=*=*AVANC�=*=*=*=*=*=*=*=*=//
		//Permet d'ex�cuter une m�thode entre 2 frames
		virtual void SendLateUpdateCommand(function<void(LE::Engine&)> InNewCommand);
		//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=//

		//Scene register/unregister
		//Log INFO: Sc�ne "InNewSceneName" est enregistr�e
		//Log ERROR: Sc�ne "InNewSceneName" existe d�j�.
		//Log ERROR: Nom fourni est vide.
		void RegisterScene(shared_ptr<LE::Scene> NewScene);
		void UnregisterScene(const string& InSceneName);
		shared_ptr<LE::Scene> FindScene(const string& InSceneName) const;
		weak_ptr<LE::Scene> GetCurrentActiveScene();

		//Si appel�, on doit ferm� l'application en quittant le "while" de mani�re propre.
		void RequestClose();

		//Change la sc�ne active
		//Log INFO: Sc�ne "InNewSceneName" maintenant active.
		//Log WARNING: Sc�ne "InNewSceneName" est d�j� activ�e.
		//Log ERROR: Sc�ne "InNewSceneName" n'existe pas.
		void SwitchScene(const string&  InNewSceneName);
		//V�rifie si la sc�ne est enregistr�e dans Engine
		bool IsSceneRegistered(const string& InNewSceneName) const;
	};
}

