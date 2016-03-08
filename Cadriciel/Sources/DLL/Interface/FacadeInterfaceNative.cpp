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
#include "ComportementTypes.h"
#include "CommandeRobot.h"
#include "ComportementAbstrait.h"
#include "CommandeRobot.h"

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
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirAngleRotation();
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
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirFacteurMiseAEchelle();
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
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPositionRelativeX();
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
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPositionRelativeY();
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
	/// @fn __declspec(dllexport) double __cdecl obtenirNombreSelection()
	///
	/// Cette fonction retourne le nombre d'objet selectionné
	///
	/// @param int : le nombre d'objet selectionné
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreSelection()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreSelection();
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
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerAngleRotation(angle);
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
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerFacteurMiseAEchelle(facteurMiseAEchelle);
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
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerPositionRelativeX(positionRelativeX);
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
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerPositionRelativeY(positionRelativeY);
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
		FacadeModele::obtenirInstance()->obtenirMode()->gererMessage(msg, wParam, lParam);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerComportementSuivreLigne(TypeComportement comportementSuivant)
	///
	/// Cette fonction permet d'assigner le comportement suivi de ligne du robot au profil de l'utilisateur.
	///
	/// @param comportementSuivant : le comportement a adopté après le comportement suivi de ligne. 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerComportementSuivreLigne(int comportementSuivant){
		std::unique_ptr<ComportementSuiviLigne> comportementPtr = std::make_unique<ComportementSuiviLigne>();
		comportementPtr->assignerComportementSuivant((TypeComportement)comportementSuivant);
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerComportement(SUIVIDELIGNE, std::move(comportementPtr));
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerComportementBalayage(TypeComportement comportementSuivant)
	///
	/// Cette fonction permet d'assigner le comportement balayage du robot au profil de l'utilisateur.
	///
	/// @param comportementSuivant : le comportement a adopté après le comportement suivi de ligne.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerComportementBalayage(int comportementSuivant){
		std::unique_ptr<ComportementBalayage> comportementPtr = std::make_unique<ComportementBalayage>();
		comportementPtr->assignerComportementSuivant((TypeComportement)comportementSuivant);
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerComportement(BALAYAGE180, std::move(comportementPtr));
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerComportementDeviation(TypeComportement comportementSuivant, double angle, TypeComportement typeDeviation)
	///
	/// Cette fonction permet d'assigner le comportement deviation gauche ou droite du robot au profil de l'utilisateur.
	///
	/// @param comportementSuivant : le comportement a adopté après le comportement suivi de ligne.
	/// @param angle : l'angle de la déviation
	///@param typeDeviation : représente si c'est une déviation à gauche ou à droite
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerComportementDeviation(int comportementSuivant, double angle, int typeDeviation){
		std::unique_ptr<ComportementDeviation> comportementPtr = std::make_unique<ComportementDeviation>();
		comportementPtr->assignerComportementSuivant(static_cast<TypeComportement>(comportementSuivant));
		comportementPtr->setAngleMaxRotation(angle);
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerComportement(static_cast<TypeComportement>(typeDeviation), std::move(comportementPtr));
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerComportementEvitement(TypeComportement comportementSuivant, double angle, double duree, TypeComportement typeEvitement)
	///
	/// Cette fonction permet d'assigner le comportement deviation gauche ou droite du robot au profil de l'utilisateur.
	///
	/// @param comportementSuivant : le comportement a adopté après le comportement suivi de ligne.
	/// @param angle : l'angle de la déviation.
	/// @param duree : la durée de l'évitement.
	/// @param typeEvitement : représente si c'est un évitement vers la gauche ou la droite
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerComportementEvitement(int comportementSuivant, double angle, double duree, int typeEvitement){
		std::unique_ptr<ComportementEvitement> comportementPtr = std::make_unique<ComportementEvitement>();
		comportementPtr->assignerComportementSuivant(static_cast<TypeComportement>(comportementSuivant));
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerComportement(static_cast<TypeComportement>(typeEvitement), std::move(comportementPtr));
	}

	__declspec(dllexport) void __cdecl modifierToucheCommande(char touche, int commande){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->modifierToucheCommande((uint8_t)touche, static_cast<TypeCommande>(commande));
	}

	__declspec(dllexport) void __cdecl chargerProfilParDefaut()
	{
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->chargerProfilParDefaut();
	}

	__declspec(dllexport) char __cdecl obtenirToucheCommande(int commande)
	{
		return FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirToucheCommande(commande);
	}

	__declspec(dllexport) void __cdecl setHandle(HWND handle, int ctrl){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->setConfigureHandles(handle, static_cast<ConfigureControl>(ctrl));
	}


	__declspec(dllexport) void __cdecl changerProfil(char* nomProfil){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->changerProfil(std::string(nomProfil));
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
