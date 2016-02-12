////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "Camera.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"
#include "EtatTypes.h"
#include "BancTests.h"

#include <iostream>

#define VK_KEY_D 0x44
#define VK_KEY_S 0x53
#define VK_KEY_R 0x52
#define VK_KEY_E 0x45
#define VK_KEY_C 0x43
#define VK_KEY_Z 0x5A
#define VK_KEY_T 0x54

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fenêtre
	/// identifiée par le handle passé en paramètre.  Cette fonction doit
	/// être la première à être appelée, car la création de l'objet du modèle
	/// C++ s'attend à avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)handle);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction libère le contexte OpenGL. Cette fonction doit être la
	/// dernière à être appelée, car elle libère également l'objet du modèle
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// Désinitialisation de la façade.  Le fait de le faire après la
		// désinitialisation du contexte OpenGL aura pour conséquence que la
		// libération des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la scène.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		
		// Affiche la scène.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour détecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit être appelée lorsque la fenêtre est
	/// redimensionnée afin d'ajuster les paramètres de la machine à états
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenêtre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fenêtre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
			glm::ivec2{ 0, 0 },
			glm::ivec2{ largeur, hauteur }
		);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
	///
	/// Cette fonction effectue les différents calculs d'animations
	/// nécessaires pour le mode jeu, tel que les différents calculs de
	/// physique du jeu.
	///
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float)temps);
	}

	__declspec(dllexport) void __cdecl sauvegarder(){
		FacadeModele::obtenirInstance()->obtenirMode()->sauvegarder();
	}

	__declspec(dllexport) void __cdecl charger(){
		FacadeModele::obtenirInstance()->obtenirMode()->charger();
	}

	__declspec(dllexport) void __cdecl assignerCheminFichierZone(char* chemin){
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerCheminFichierZone(string(chemin));
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arrière sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerEtat(int etat)
	///
	/// Cette fonction permet d'assigner un Etat
	///
	/// @param int etat : Le numero de l'état selectionné
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerEtat(int etat)
	{
		FacadeModele::obtenirInstance()->assignerEtat((Etat)etat);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl obtenirEtat()
	///
	/// Cette fonction permet d'obtenir un Etat
	///
	/// @return int etat : Le numero du mode sélectionné
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirEtat()
	{
		return (int)FacadeModele::obtenirInstance()->obtenirEtat()->obtenirTypeEtat();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerMode(int mode)
	///
	/// Cette fonction permet d'assigner un Mode
	///
	/// @param int mode : Le numero du mode sélectionné
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerMode(int mode)
	{
		FacadeModele::obtenirInstance()->assignerMode((Mode)mode);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl obtenirMode()
	///
	/// Cette fonction permet d'obtenir un Mode
	///
	/// @return int mode : Le numero du mode sélectionné
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirMode()
	{
		return FacadeModele::obtenirInstance()->obtenirMode()->obtenirTypeMode();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double __cdecl obtenirAngleRotation()
	///
	/// Cette fonction permet d'obtenir l'angle de rotation d'un objet
	///
	/// @return doublee : l'angle de rotation de l'objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl obtenirAngleRotation()
	{
		return FacadeModele::obtenirInstance()->obtenirAngleRotation();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double obtenirFacteurGrandeur()
	///
	/// Cette fonction permet d'obtenir le facteur de grandissement d'un objet
	///
	/// @return doublee : le facteur de grandissement d'un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double obtenirFacteurGrandeur()
	{
		return FacadeModele::obtenirInstance()->obtenirFacteurGrandeur();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double obtenirPositionRelativeX()
	///
	/// Cette fonction permet d'obtenir la position relative en X
	///
	/// @return doublee : la position relative en X
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double obtenirPositionRelativeX()
	{
		return FacadeModele::obtenirInstance()->obtenirPositionRelativeX();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double obtenirPositionRelativeX()
	///
	/// Cette fonction permet d'obtenir la position relative en Y
	///
	/// @return doublee : la position relative en Y
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double obtenirPositionRelativeY()
	{
		return FacadeModele::obtenirInstance()->obtenirPositionRelativeY();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl nouvelleTable()
	///
	/// Cette fonction permet de supprimer tous les objets de la table
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl nouvelleTable()
	{
		FacadeModele::obtenirInstance()->reinitialiser();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl suppression()
	///
	/// Cette fonction permet de supprimer un objet selectionné
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl suppression()
	{
		FacadeModele::obtenirInstance()->obtenirMode()->gererToucheSupprimer();
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double __cdecl obtenirNombreSelection()
	///
	/// Cette fonction retourne le nombre d'objet selectionné
	///
	/// @param int : le nombre d'objet selectionné
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreSelection()
	{
		return FacadeModele::obtenirInstance()->obtenirNombreSelection();
	}

	__declspec(dllexport) void assignerAngleRotation(double angle)
	{
		FacadeModele::obtenirInstance()->assignerAngleRotation(angle);
	}

	__declspec(dllexport) void assignerFacteurGrandeur(double facteurGrandeur)
	{
		FacadeModele::obtenirInstance()->assignerFacteurGrandeur(facteurGrandeur);
	}

	__declspec(dllexport) void assignerPositionRelativeX(double positionRelativeX)
	{
		FacadeModele::obtenirInstance()->assignerPositionRelativeX(positionRelativeX);
	}

	__declspec(dllexport) void assignerPositionRelativeY(double positionRelativeY)
	{
		FacadeModele::obtenirInstance()->assignerPositionRelativeY(positionRelativeY);
	}

	__declspec(dllexport) void repartirMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{

		if (msg == WM_KEYDOWN)
		{
			switch (wParam)
			{
				// voir http://www.kbdedit.com/manual/low_level_vk_list.html 
				case VK_LEFT:
					FacadeModele::obtenirInstance()->obtenirMode()->gererFlecheGauche();
					break;

				case VK_RIGHT:
					FacadeModele::obtenirInstance()->obtenirMode()->gererFlecheDroit();
					break;

				case VK_UP:
					FacadeModele::obtenirInstance()->obtenirMode()->gererFlecheHaut();
					break;

				case VK_DOWN:
					FacadeModele::obtenirInstance()->obtenirMode()->gererFlecheBas();
					break;

				case VK_TAB:
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().assignerPosition({0, 0, 10});
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().assignerDirectionHaut({0, 1, 0});
					break;

				case VK_BACK:
					break;

				case VK_SHIFT:
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().assignerPosition({0, 10, 0});
					FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().assignerDirectionHaut({0, 0, 1});
					break;

				case VK_MENU:
				case VK_RMENU:
				case VK_LMENU:
					std::cout << "La touche alt est appuyee" << std::endl;
					FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheAltEnfoncee();
					break;

				case VK_CONTROL:
				case VK_RCONTROL:
				case VK_LCONTROL:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheControlEnfoncee();
					break;

				case VK_ESCAPE:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheEchappe();
					break;

				case VK_OEM_PLUS:
					FacadeModele::obtenirInstance()->obtenirMode()->gererTouchePlus();
					break;

				case VK_OEM_MINUS:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheMoins();
					break;

				case VK_KEY_D:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheD();
					break;

				case VK_KEY_S:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheS();
					break;

				case VK_KEY_R:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheR();
					break;

				case VK_KEY_E:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheE();
					break;

				case VK_KEY_C:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheC();
					break;

				case VK_KEY_Z:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheZ();
					break;

				case VK_KEY_T:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheT();
					break;


				case VK_DELETE:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheSupprimer();
					break;


				default:
					break;
			}
		}

		if (msg == WM_KEYUP)
		{
			switch (wParam)
			{
				case VK_CONTROL:
				case VK_LCONTROL:
				case VK_RCONTROL:
					FacadeModele::obtenirInstance()->obtenirMode()->gererToucheControlRelachee();
					break;

				case VK_MENU:
				case VK_RMENU:
				case VK_LMENU:
					std::cout << "La touche alt est relachee" << std::endl;
					FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheAltRelachee();
					break;

				default:
					break;
			}
		}

		switch (msg)
		{
		case WM_LBUTTONDOWN:
			FacadeModele::obtenirInstance()->obtenirMode()->gererClicGaucheEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_LBUTTONUP:
			FacadeModele::obtenirInstance()->obtenirMode()->gererClicGaucheRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_RBUTTONDOWN:
			FacadeModele::obtenirInstance()->obtenirMode()->gererClicDroitEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_RBUTTONUP:
			FacadeModele::obtenirInstance()->obtenirMode()->gererClicDroitRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_MOUSEMOVE:
			FacadeModele::obtenirInstance()->obtenirMode()->gererMouvementSouris(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_MOUSEWHEEL:
			FacadeModele::obtenirInstance()->obtenirMode()->gererMoletteSouris(GET_WHEEL_DELTA_WPARAM(wParam));
			break;

		//case WM_SETCURSOR:
			//FacadeModele::obtenirInstance()->obtenirEtat()->assignerSymbolePointeur();
		}
	}


}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////