////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include <string>

#include "glm\glm.hpp"
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "Camera.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"
#include "EtatTypes.h"
#include "BancTests.h"


const int VK_KEY_D = 0x44;
const int VK_KEY_S = 0x53;
const int VK_KEY_R = 0x52;
const int VK_KEY_E = 0x45;
const int VK_KEY_C = 0x43;
const int VK_KEY_Z = 0x5A;
const int VK_KEY_T = 0x54;

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
		if (handle == nullptr) {
			return;
		}
		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)(handle));
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

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl sauvegarder()
	///
	/// Cette fonction écrit la structure de l'arbre de rendu dans un fichier qui a été charger au préalable.
	///
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sauvegarder(){
		FacadeModele::obtenirInstance()->obtenirMode()->sauvegarder();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl charger()
	///
	/// Cette fonction charge un fichier sélectionné par l'utilisateur.
	///
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl charger(){
		FacadeModele::obtenirInstance()->obtenirMode()->charger();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerCheminFichierZone(char* chemin)
	///
	/// Cette fonction assigne le chemin vers le fichier sélectionné par l'utilisateur.
	///
	/// @param[in] chemin : chemin vers le fichier de zone
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerCheminFichierZone(char* chemin){
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerCheminFichierZone(std::string(chemin));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl obtenirCheminFichierZoneDefaut(char* chemin, int longueur)
	///
	/// Cette fonction permet d'obtenir le chemin vers le fichier de zone par défaut.
	///
	/// @param[in] chemin : contenur pour la string représentant le chemin versle fichier de zone par défaut
	/// @param[in] longueur : taille du conteneur
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obtenirCheminFichierZoneDefaut(char* chemin, int longueur){
		strcpy_s(chemin, longueur, FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirCheminFichierZoneDefaut().c_str());
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
		FacadeModele::obtenirInstance()->assignerMode((Mode)(mode));
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
	__declspec(dllexport) double __cdecl obtenirFacteurGrandeur()
	{
		return FacadeModele::obtenirInstance()->obtenirFacteurMiseAEchelle();
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
	__declspec(dllexport) double __cdecl obtenirPositionRelativeX()
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
	__declspec(dllexport) double __cdecl obtenirPositionRelativeY()
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

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl obtenirAutorisationInputClavier()
	///
	/// Cette fonction retourne l'autorisation des inputs claviers
	///
	/// @return bool : l'autorisation des inputs claviers
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl obtenirAutorisationInputClavier()
	{
		return FacadeModele::obtenirInstance()->obtenirAutorisationInputClavier();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerAutorisationInputClavier(bool autorisation)
	///
	/// Cette fonction assigne l'autorisation des inputs claviers
	///
	/// @param bool : l'autorisation des inputs claviers
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerAutorisationInputClavier(bool autorisation)
	{
		FacadeModele::obtenirInstance()->assignerAutorisationInputClavier(autorisation);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl obtenirAutorisationInputSouris()
	///
	/// Cette fonction retourne l'autorisation des inputs souris
	///
	/// @return bool : l'autorisation des inputs souris
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl obtenirAutorisationInputSouris()
	{
		return FacadeModele::obtenirInstance()->obtenirAutorisationInputSouris();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerAutorisationInputSouris(bool autorisation)
	///
	/// Cette fonction assigne l'autorisation des inputs souris
	///
	/// @param bool : l'autorisation des inputs souris
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerAutorisationInputSouris(bool autorisation)
	{
		FacadeModele::obtenirInstance()->assignerAutorisationInputSouris(autorisation);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerAngleRotation(double angle)
	///
	/// Cette fonction permet d'assigner l'angle de rotation
	///
	/// @param double : l'angle de rotation.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void assignerAngleRotation(double angle)
	{
		FacadeModele::obtenirInstance()->assignerAngleRotation(angle);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerFacteurGrandeur(facteurMiseAEchelle)
	///
	/// Cette fonction permet d'assigner le facteur de mise à échelle.
	///
	/// @param double : l'angle de rotation.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerFacteurGrandeur(double facteurMiseAEchelle)
	{
		FacadeModele::obtenirInstance()->assignerFacteurMiseAEchelle(facteurMiseAEchelle);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerPositionRelativeX(positionRelativeX)
	///
	///	Cette fonction permmet d'assigner une position relative en X.
	///
	/// @param positionRelativeX : la position relative en X. 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerPositionRelativeX(double positionRelativeX)
	{
		FacadeModele::obtenirInstance()->assignerPositionRelativeX(positionRelativeX);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerPositionRelativeY(positionRelativeY)
	///
	/// Cette fonction permet d'assigner une position relative en Y.
	///
	/// @param positionRelativeX : la position relative en Y. 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerPositionRelativeY(double positionRelativeY)
	{
		FacadeModele::obtenirInstance()->assignerPositionRelativeY(positionRelativeY);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl repartirMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	///
	/// Cette fonction permet de repartir le traitement de certains messages provenant de l'interface utilisateur,
	/// principalement les messages concerant les entrées avec la souris et le clavier.
	/// Voir https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx/ 
	///	pour la documentation sur la signification des codes virtuels.
	///
	/// @param UINT msg : L'identificateur du message.
	///
	/// @param WPARAM wParam : Information additionnelle du message. 
	///
	/// @param LPARAM lParam : Information additionnelle du message.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl repartirMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		bool autoriserInput = FacadeModele::obtenirInstance()->obtenirAutorisationInputClavier();
		if (autoriserInput) {
			if (msg == WM_KEYDOWN) {
				switch (wParam) {
					case VK_LEFT :
						FacadeModele::obtenirInstance()->obtenirMode()->gererFlecheGauche();
						break;

					case VK_RIGHT :
						FacadeModele::obtenirInstance()->obtenirMode()->gererFlecheDroit();
						break;

					case VK_UP :
						FacadeModele::obtenirInstance()->obtenirMode()->gererFlecheHaut();
						break;

					case VK_DOWN :
						FacadeModele::obtenirInstance()->obtenirMode()->gererFlecheBas();
						break;

					case VK_BACK :
						break;

					case VK_ESCAPE :
						FacadeModele::obtenirInstance()->obtenirMode()->gererToucheEchappe();
						break;

					case VK_OEM_PLUS :
						FacadeModele::obtenirInstance()->obtenirMode()->gererTouchePlus();
						break;

					case VK_OEM_MINUS :
						FacadeModele::obtenirInstance()->obtenirMode()->gererToucheMoins();
						break;

					case VK_KEY_D:
						FacadeModele::obtenirInstance()->obtenirMode()->gererToucheD();
						break;

					case VK_KEY_S:
						if (!GetKeyState(VK_CONTROL)) {
							FacadeModele::obtenirInstance()->obtenirMode()->gererToucheS();
						}
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


					case VK_DELETE :
						FacadeModele::obtenirInstance()->obtenirMode()->gererToucheSupprimer();
						break;

					case VK_MENU:
						// Poursuivre.
					case VK_LMENU:
						// Poursuivre.
					case VK_RMENU:
						FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheAltEnfoncee();
						break;

					case VK_CONTROL :
						// Poursuivre.
					case VK_LCONTROL :
						// Poursuivre.
					case VK_RCONTROL :
						// Poursuivre.
						FacadeModele::obtenirInstance()->obtenirMode()->gererToucheControlEnfoncee();
						break;

					default:
						break;
				}
			}

			// Répartition du traitement des touches relachées.
			if (msg == WM_KEYUP) {
				switch (wParam) {
					case VK_MENU :
						// Poursuivre.
					case VK_LMENU :
						// Poursuivre.
					case VK_RMENU :
						FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheAltRelachee();
						break;

					case VK_CONTROL :
						// Poursuivre.
					case VK_RCONTROL :
						// Poursuivre.
					case VK_LCONTROL :
						FacadeModele::obtenirInstance()->obtenirMode()->gererToucheControlRelachee();
						break;

					default:
						break;
				}
			}
			// Répartition du traitement des touches enfoncées provenant du système pour les différents types de claviers.
			if (msg == WM_SYSKEYDOWN) {
				switch (wParam)	{
					case VK_MENU :
						// Poursuivre.
					case VK_LMENU :
						// Poursuivre.
					case VK_RMENU :
						FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheAltEnfoncee();
						break;

					case VK_CONTROL :
						// Poursuivre.
					case VK_LCONTROL :
						// Poursuivre.
					case VK_RCONTROL :
						FacadeModele::obtenirInstance()->obtenirMode()->gererToucheControlEnfoncee();
						break;
				}
			}
			// Répartition du traitement des touches relâchées provenant du système pour les différents types de claviers.
			if (msg == WM_SYSKEYUP) {
				switch (wParam) {
					case VK_MENU :
						// Poursuivre.
					case VK_LMENU :
						// Poursuivre.
					case VK_RMENU :
						FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheAltRelachee();
						break;

					case VK_CONTROL :
						// Poursuivre.
					case VK_RCONTROL :
						// Poursuivre.
					case VK_LCONTROL :
						FacadeModele::obtenirInstance()->obtenirMode()->gererToucheControlRelachee();
						break;
				}
			}
		}
		// Répartition du traitement des messages provenant de la souris.
		if (FacadeModele::obtenirInstance()->obtenirAutorisationInputSouris()) {
			switch (msg)
			{
				case WM_LBUTTONDBLCLK :
				case WM_LBUTTONDOWN :
					FacadeModele::obtenirInstance()->obtenirMode()->gererClicGaucheEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					break;

				case WM_LBUTTONUP :
					FacadeModele::obtenirInstance()->obtenirMode()->gererClicGaucheRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					break;

				case WM_RBUTTONDBLCLK :
				case WM_RBUTTONDOWN :
					FacadeModele::obtenirInstance()->obtenirMode()->gererClicDroitEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					break;

				case WM_RBUTTONUP :
					FacadeModele::obtenirInstance()->obtenirMode()->gererClicDroitRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					break;

				case WM_MOUSEMOVE :
					FacadeModele::obtenirInstance()->obtenirMode()->gererMouvementSouris(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					break;

				case WM_MOUSEWHEEL :
					FacadeModele::obtenirInstance()->obtenirMode()->gererMoletteSouris(GET_WHEEL_DELTA_WPARAM(wParam));
					break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
