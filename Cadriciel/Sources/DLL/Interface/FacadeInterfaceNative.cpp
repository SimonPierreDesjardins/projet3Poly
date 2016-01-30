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

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND) handle);
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
		FacadeModele::obtenirInstance()->animer((float) temps);
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


	__declspec(dllexport) void __cdecl assignerEtat(int etat)
	{
		FacadeModele::obtenirInstance()->assignerEtat((Etat)etat);
	}

	__declspec(dllexport) void repartirMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{	
		if (msg == WM_KEYDOWN)
		{
			switch (wParam)
			{
				// voir http://www.kbdedit.com/manual/low_level_vk_list.html 
				case VK_LEFT:
					std::cout << "La fleche de gauche est appuyee" << std::endl;
					FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(-10, 0);
					break;

				case VK_RIGHT:
					std::cout << "La fleche de droite est appuyee" << std::endl;
					FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(10, 0);
					break;

				case VK_UP:
					std::cout << "La fleche du haut est appuyee" << std::endl;
					FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, 10);
					break;

				case VK_DOWN:
					std::cout << "La fleche du bas est appuyee" << std::endl;
					FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, -10);
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
					break;

				case VK_CONTROL:
				case VK_RCONTROL:
				case VK_LCONTROL:
					FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheControlEnfoncee();
					break;

				case VK_ESCAPE:
					FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheEchappe();
					break;
				case VK_OEM_PLUS:
					FacadeModele::obtenirInstance()->obtenirEtat()->gererTouchePlus();
					break;
				case VK_OEM_MINUS:
					FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheMoins();
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
					FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheControlRelachee();
					break;

				default:
					break;
			}
		}

		switch (msg)
		{
			case WM_LBUTTONDOWN :
				FacadeModele::obtenirInstance()->obtenirEtat()->gererClicGaucheEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				break;
			
			case WM_LBUTTONUP :
				FacadeModele::obtenirInstance()->obtenirEtat()->gererClicGaucheRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				break;
			
			case WM_RBUTTONDOWN :
				FacadeModele::obtenirInstance()->obtenirEtat()->gererClicDroitEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				break;
			
			case WM_RBUTTONUP :
				FacadeModele::obtenirInstance()->obtenirEtat()->gererClicDroitRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				break;

			case WM_MOUSEMOVE :
				FacadeModele::obtenirInstance()->obtenirEtat()->gererMouvementSouris(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));	
				break;

			case WM_MOUSEWHEEL:
				FacadeModele::obtenirInstance()->obtenirEtat()->gererMoletteSouris(GET_WHEEL_DELTA_WPARAM(wParam));
				break;
		}
	}


}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////