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
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "Camera.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"
#include "EtatTypes.h"
#include "ComportementTypes.h"
#include "CommandeRobot.h"
#include "ComportementAbstrait.h"
#include "CommandeRobot.h"
#include "EnginSon.h"
#include "Projection.h"
#include "ModeTypes.h"

#include "FacadeInterfaceNative.h"

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fen�tre
	/// identifi�e par le handle pass� en param�tre.  Cette fonction doit
	/// �tre la premi�re � �tre appel�e, car la cr�ation de l'objet du mod�le
	/// C++ s'attend � avoir un contexte OpenGL valide.
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
		FacadeModele::obtenirInstance()->initialize((HWND)(handle));
        //executerTests();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction lib�re le contexte OpenGL. Cette fonction doit �tre la
	/// derni�re � �tre appel�e, car elle lib�re �galement l'objet du mod�le
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// D�sinitialisation de la fa�ade.  Le fait de le faire apr�s la
		// d�sinitialisation du contexte OpenGL aura pour cons�quence que la
		// lib�ration des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
		EnginSon::libererInstance();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la sc�ne.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		
		// Affiche la sc�ne.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour d�tecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit �tre appel�e lorsque la fen�tre est
	/// redimensionn�e afin d'ajuster les param�tres de la machine � �tats
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fen�tre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fen�tre.
	/// @param[in] hauteur : La nouvelle hauteur de la fen�tre.
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
	/// Cette fonction effectue les diff�rents calculs d'animations
	/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
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
	/// Cette fonction �crit la structure de l'arbre de rendu dans un fichier qui a �t� charger au pr�alable.
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
	/// Cette fonction charge un fichier s�lectionn� par l'utilisateur.
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
	/// Cette fonction assigne le chemin vers le fichier s�lectionn� par l'utilisateur.
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
	/// Cette fonction permet d'obtenir le chemin vers le fichier de zone par d�faut.
	///
	/// @param[in] chemin : contenur pour la string repr�sentant le chemin versle fichier de zone par d�faut
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
	/// @fn __declspec(dllexport) void __cdecl assignerMode(int mode)
	///
	/// Cette fonction permet d'assigner un Mode
	///
	/// @param int mode : Le numero du mode s�lectionn�
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
	/// @return int mode : Le numero du mode s�lectionn�
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
	/// Cette fonction retourne le nombre d'objet selectionn�
	///
	/// @param int : le nombre d'objet selectionn�
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
	/// Cette fonction permet d'assigner le facteur de mise � �chelle.
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
	/// principalement les messages concerant les entr�es avec la souris et le clavier.
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
	/// @param comportementSuivant : le comportement a adopt� apr�s le comportement suivi de ligne. 
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
	/// @param comportementSuivant : le comportement a adopt� apr�s le comportement suivi de ligne.
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
	/// @param comportementSuivant : le comportement a adopt� apr�s le comportement suivi de ligne.
	/// @param angle : l'angle de la d�viation
	///@param typeDeviation : repr�sente si c'est une d�viation � gauche ou � droite
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerComportementDeviation(int comportementSuivant, double angle, int typeDeviation){
		// v�rifions si une modification de l'angle es n�cessaire.
		if (static_cast<TypeComportement>(typeDeviation) == DEVIATIONVERSLADROITE){
			angle *= -1;
		}
		std::unique_ptr<ComportementDeviation> comportementPtr = std::make_unique<ComportementDeviation>(static_cast<TypeComportement>(comportementSuivant), angle);
		comportementPtr->assignerComportementSuivant(static_cast<TypeComportement>(comportementSuivant));
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerComportement(static_cast<TypeComportement>(typeDeviation), std::move(comportementPtr));
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerComportementEvitement(TypeComportement comportementSuivant, double angle, double duree, TypeComportement typeEvitement)
	///
	/// Cette fonction permet d'assigner le comportement deviation gauche ou droite du robot au profil de l'utilisateur.
	///
	/// @param comportementSuivant : le comportement a adopt� apr�s le comportement suivi de ligne.
	/// @param angle : l'angle de la d�viation.
	/// @param duree : la dur�e de l'�vitement.
	/// @param typeEvitement : repr�sente si c'est un �vitement vers la gauche ou la droite
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerComportementEvitement(int comportementSuivant, double angle, double duree, int typeEvitement){
		// v�rifions si une modification de l'angle es n�cessaire.
		if (static_cast<TypeComportement>(typeEvitement) == EVITEMENTPARLADROITE){
			angle *= -1;
		}
		std::unique_ptr<ComportementEvitement> comportementPtr = std::make_unique<ComportementEvitement>(static_cast<TypeComportement>(comportementSuivant), duree, angle);
		comportementPtr->assignerComportementSuivant(static_cast<TypeComportement>(comportementSuivant));
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerComportement(static_cast<TypeComportement>(typeEvitement), std::move(comportementPtr));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerCapteurDistance(bool estActif, int comportementDanger, double distanceDanger, int comportementSecuritaire, double distanceSecuritaire, int indexCapteur)
	///
	/// Fonction servant � modifier les capteurs de distance du robot.
	/// Fait le pont entre l'interface et le mod�le
	///
	/// @param[in] estActif : repr�sente si le capteur est actif ou non
	/// @param[in] comportementDanger : enum repr�sentant le comportement � adpoter dans une zone de danger
	/// @param[in] distanceDanger : la grandeur de la zone de danger
	/// @param[in] comportementSecuritaire : enum repr�sentant le comportement � adpoter dans une zone s�curitaire
	/// @param[in] distanceSecuritaire : la grandeur de la zone s�curitaire
	/// @param[in] indexCapteur : le capteur � modifier (0 � 2)
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerCapteurDistance(bool estActif, int comportementDanger, double distanceDanger, int comportementSecuritaire, double distanceSecuritaire, int indexCapteur){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerCapteurDistance(estActif, static_cast<TypeComportement>(comportementDanger), distanceDanger, static_cast<TypeComportement>(comportementSecuritaire), distanceSecuritaire, indexCapteur);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerSuiveurLigne(bool estActif)
	///
	///	Fonction servant � modifier le suiveur de ligne du robot.
	/// Fait le pont entre l'interface et le mod�le
	///
	/// @param[in] estActif : repr�sente si le suiveur de ligne est actif ou non
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerSuiveurLigne(bool estActif){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerSuiveurLigne(estActif);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerOptionsDebogages(bool debogageActif, bool debogageComportements, bool debogageEclairage, bool debogageCapteurs)
	/// 
	///	Fonction servant � activer ou d�sactiver les options de d�bogages.
	/// Fait le pont entre l'interface et le mod�le
	///
	/// @param[in] optionsDebogages[] : tableau contenant l'�tat des options de d�bogages
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerOptionsDebogages(bool debogageActif, bool debogageComportements, bool debogageEclairage, bool debogageCapteurs){
		bool optionsDebogages[] = { debogageActif, debogageComportements, debogageEclairage, debogageCapteurs };
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerOptionsDebogages(optionsDebogages);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl modifierToucheCommande(char touche, int commande)
	///
	///	Fonction servant � modifier une des touches associ� � une commande pour contr�ler le robot.
	/// Fait le pont entre l'interface et le mod�le
	///
	/// @param[in] touche : la nouvelle touche
	/// @param[in] commande : la commande dont la touche doit �tre modifi�e
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl modifierToucheCommande(char touche, int commande){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->modifierToucheCommande((uint8_t)touche, static_cast<TypeCommande>(commande));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl obtenirNomProfilDefaut(char* nom, int longueur)
	///
	///	Fonction servant � obtenir le nom du profil par d�faut
	/// Fait le pont entre l'interface et le mod�le
	///
	/// @param[in] nom : contient le nom du profil par d�faut
	/// @param[in] longueur : la longueur du nom
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obtenirNomProfilDefaut(char* nom, int longueur){
		strcpy_s(nom, longueur, FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirNomProfilDefaut().c_str());
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl obtenirNomDernierProfil(char* nom, int longueur)
	///
	/// Fonction servant � obtenir le nom du dernier profil charg�
	/// Fait le pont entre l'interface et le mod�le
	///
	/// @param[in] nom : contient le nom du dernier profil
	/// @param[in] longueur : la longueur du nom
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obtenirNomDernierProfil(char* nom, int longueur){
		strcpy_s(nom, longueur, FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirNomDernierProfil().c_str());
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl chargerDernierProfil()
	///
	///	Fonction servant � charger le dernier profil charg� lors de la derni�re utilisation.
	/// Si ce profil n'existe pas on charge le profil par d�faut.
	/// Fait le pont entre l'interface et le mod�le.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl chargerDernierProfil()
	{
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->chargerDernierProfil();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl sauvegarderProfil(char* nomProfil)
	///
	///	Fonction servant � sauvegarder ou cr�er le fichier d'un profil d'un certain nom.
	/// Fait le pont entre l'interface et le mod�le.
	///
	/// @param[in] nomProfil : le nom du profil � sauvegarder
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sauvegarderProfil(char* nomProfil){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->sauvegarder(std::string(nomProfil));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) char __cdecl obtenirToucheCommande(int commande)
	///
	///	Fonction servant � obtenir la touche associ�e � une commande.
	/// Fait le pont entre l'interface et le mod�le.
	///
	/// @param[in] commande : la commande dont l'on veut la touche.
	///
	/// @return char La touche associ�e � la commande.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char __cdecl obtenirToucheCommande(int commande)
	{
		return FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirToucheCommande(commande);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerConfigureHandles(HWND handle, int ctrl)
	///
	///	Fonction servant � assigner les handles des contr�les d'interface de la fen�tre Configuration pour ainsi les modifier � partir du mod�le.
	/// Fait le pont entre l'interface et le mod�le.
	///
	/// @param[in] handle : la handle d'un des contr�les d'interface
	/// @param[in] ctrl : enum repr�sentant le contr�le dont on assigne la handle
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerConfigureHandles(HWND handle, int ctrl){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerConfigureHandles(handle, static_cast<ConfigureControl>(ctrl));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl changerProfil(char* nomProfil)
	///
	///	Fonction servant � charger un nouveau profil. Si le profil n'existe pas, un contenant les param�tres par d�faut est cr�� avec le nom pass� en argument.
	/// Fait le pont entre l'interface et le mod�le.
	///
	/// @param[in] nomProfil : le nom du profil que l'on veut charger.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changerProfil(char* nomProfil){
		auto mode = FacadeModele::obtenirInstance()->obtenirMode();

		if (mode != nullptr){
			mode->preChangementDeProfil();
		}

		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->changerProfil(std::string(nomProfil));

		if (mode != nullptr){
			mode->postChangementDeProfil();
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl obtenirCheminProfils(char* chemin, int longueur)
	///
	///	Fonction servant � obtenir le chemin vers le dossier Donnees
	/// Fait le pont entre l'interface et le mod�le.
	///
	/// @param[in] chemin : chemin vers le dossier Donnees
	/// @param[in] longueur : nombre de caract�res dans le chemin
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obtenirCheminProfils(char* chemin, int longueur){
		strcpy_s(chemin, longueur, FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirCheminProfils().c_str());
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl obtenirExtensionProfils(char* extension, int longueur)
	///
	///	Fonction retournant l'extension d'un fichier de type profil
	/// Fait le pont entre l'interface et le mod�le.
	///
	/// @param[in] extension : extension d'un fichier de type profil
	/// @param[in] longueur : nombre de caract�res dans l'extension
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obtenirExtensionProfils(char* extension, int longueur){
		strcpy_s(extension, longueur, FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirExtensionProfils().c_str());
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl supprimerProfil(char* nomProfil)
	///
	///	Fonction servant � supprimer le fichier d'un certain profil.
	/// Fait le pont entre l'interface et le mod�le.
	///
	/// @param[in] nomProfil : le nom du profil � supprimer
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl supprimerProfil(char* nomProfil){
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->supprimerProfil(std::string(nomProfil));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int* __cdecl obtenirLimitesParametres()
	///
	///	Fonction retournant les limites sur les param�tres de comportement du robot
	/// Fait le pont entre l'interface et le mod�le.
	///
	/// @return int* Pointeur sur le tableau de limites
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int* __cdecl obtenirLimitesParametres(){
		return FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirLimiteParametres();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerVueOrtho()
	///
	///	Fonction qui assigne la vue en mode ortho
	///
	/// @return aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerVueOrtho()
	{
		FacadeModele::obtenirInstance()->assignerVueOrtho();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerVueOrbite()
	///
	///	Fonction qui assigne la vue en mode orbite
	///
	/// @return aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerVueOrbite()
	{
		FacadeModele::obtenirInstance()->assignerVueOrbite();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl assignerVuePremierePersonne()
	///
	///	Fonction qui assigne la vue en mode premiere personne
	///
	/// @return aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerVuePremierePersonne()
	{
		FacadeModele::obtenirInstance()->assignerVuePremierePersonne();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirTypeVue()
	///
	///	Fonction renvoyant un integer repr�sentant la vue courante.
	///
	/// @return Int
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTypeVue()
	{
		vue::Vue* vue = FacadeModele::obtenirInstance()->obtenirVue();
		if (vue->estPremierePersonne())
			return 2;
		else if (vue->obtenirProjection().estPerspective() && !vue->estPremierePersonne())
			return 1;
		else
			return 0;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl getUsingDefaultMaterialForPiece(int piece)
	///
	///	Fonction retourne si le profil utilise la couleur par defaut ou non
	///
	/// @return bool
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl getUsingDefaultMaterialForPiece(int piece)
	{
		return FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirCouleurParDefaut(piece);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl setUsingDefaultMaterialForPiece(int piece, bool value)
	///
	///	Fonction qui attribue la couleur par defaut
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setUsingDefaultMaterialForPiece(int piece, bool value)
	{
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->setCouleurParDefaut(piece, value);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->getModele())->setCouleurDefault(piece,value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl changePieceColor(int piece, int a, int r, int g, int b)
	///
	///	Fonction qui attribue la couleur sur la piece en question
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changePieceColor(int piece, int a, int r, int g, int b)
	{	
		FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->assignerCouleur(piece, a, r, g, b);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->getModele())->assignerCouleurs(piece,a,r,g,b);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int* __cdecl getPieceColor(int piece)
	///
	///	Fonction qui retourne la couleur de la piece en question
	///
	/// @return tableau contenant les couleurs
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int* __cdecl getPieceColor(int piece)
	{
		float* couleurPieceFloat = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->obtenirCouleurs(piece);
		int couleurPieceInt[4];
		
		couleurPieceInt[0] = (int)(couleurPieceFloat[0] * 255);
		couleurPieceInt[1] = (int)(couleurPieceFloat[1] * 255);
		couleurPieceInt[2] = (int)(couleurPieceFloat[2] * 255);
		couleurPieceInt[3] = (int)(couleurPieceFloat[3] * 255);

		return couleurPieceInt;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl setModele(int modele)
	///
	///	Fonction qui attribue le modele choisi
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setModele(char *modele)
	{
		if (FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->getModele() != modele)
		{
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->getModele()));
			FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->setModele(std::string(modele));
			FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->setCouleurParDefaut(BODY, true);
			FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->setCouleurParDefaut(WHEELS, true);
			FacadeModele::obtenirInstance()->obtenirMode()->creerControleRobot();
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->getModele())->setCouleurDefault(BODY, true);
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->getModele())->setCouleurDefault(WHEELS, true);
		}
		
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl getModele(char* chemin, int longueur)
	///
	///	Fonction qui get le modele
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl getModele(char* chemin, int longueur)
	{
		strcpy_s(chemin, longueur, FacadeModele::obtenirInstance()->obtenirProfilUtilisateur()->getModele().c_str());
	}

	__declspec(dllexport) void __cdecl createMap(char* mapName, int size, char mapType)
	{
		FacadeModele::obtenirInstance()->getNetworkManager()->requestMapCreation(std::string(mapName, size), mapType);
	}

	__declspec(dllexport) void __cdecl joinMap(int mapId)
	{
		FacadeModele::obtenirInstance()->getNetworkManager()->requestToJoinMapSession(mapId);
	}

	__declspec(dllexport) void __cdecl leaveMap()
	{
		FacadeModele::obtenirInstance()->getNetworkManager()->requestToQuitMapSession();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl connectToServer(char* hostName, char* port)
	///
	/// Fonction qui permet de lancer une tentative de connexion avec le serveur.
	///
	/// @param hostName : L'adresse ip du serveur.
	/// @param port     : Le port du serveur.
	/// @return bool    : True si la tentative a r�ussi.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl connectToServer(char* hostName, char* port)
	{
		return FacadeModele::obtenirInstance()->getNetworkManager()->requestConnection(std::string(hostName), std::string(port));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl createProfile(char* profileName)
	///
	/// Fonction qui permet d'envoyer une requ�te de cr�ation de profile au serveur.
	///
	/// @param profileName : Le nom du profile.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl createProfile(char* profileName)
	{
		FacadeModele::obtenirInstance()->getNetworkManager()->createProfile(std::string(profileName));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl authenticate(char* profileName)
	///
	/// Fonction qui permet d'envoyer une requ�te d'authentification au serveur.
	///
	/// @param profileName : Le nom du profile.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl authenticate(char* profileName)
	{
		FacadeModele::obtenirInstance()->getNetworkManager()->authenticate(std::string(profileName));
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl disconnectFromServer()
	///
	/// Fonction qui ferme la connexion du client.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl disconnectFromServer()
	{
		FacadeModele::obtenirInstance()->getNetworkManager()->closeConnection();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl isConnected()
	///
	/// Fonction qui retourne si le client est connect�.
	///
	/// @return bool : True si le client est connect�.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl isConnected()
	{
		return FacadeModele::obtenirInstance()->getNetworkManager()->isConnected();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl sendMessage(char const* message, int size)
	///
	/// Fonction qui permet d'envoyer un message au serveur
	///
	/// @param message : Un pointeur sur un array de char 
	/// @param size : La taille du message 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sendMessage(char* message, int size)
	{
		// Need the size of the array so the string builder doesn't stop at 
		// the first \0 (likely in the serialized message size)
		FacadeModele::obtenirInstance()->getNetworkManager()->sendSizePrefixedMessage(std::string(message, size));
	}

	CallbackDisconnect DisconnectHandler = 0;
	__declspec(dllexport) void __cdecl SetCallbackForDisconnect(CallbackDisconnect disconnectHandler)
	{
		DisconnectHandler = disconnectHandler;
	}

	__declspec(dllexport) void __cdecl GotDisconnected()
	{
		DisconnectHandler();
	}

	CallbackConnectionSuccess ConnectionSuccessHandler = 0;
	__declspec(dllexport) void __cdecl SetCallbackForConnectionSuccess(CallbackConnectionSuccess connectionSuccessHandler)
	{
		ConnectionSuccessHandler = connectionSuccessHandler;
	}

	__declspec(dllexport) void __cdecl connectionWasSuccess()
	{
		ConnectionSuccessHandler();
	}

	CallbackConnectionFail ConnectionFailHandler = 0;
	__declspec(dllexport) void __cdecl SetCallbackForConnectionFail(CallbackConnectionFail connectionFailHandler)
	{
		ConnectionFailHandler = connectionFailHandler;
	}

	__declspec(dllexport) void __cdecl connectionWasFail()
	{
		ConnectionFailHandler();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl SetCallback(Callback function)
	///
	/// Fonction qui assigne une r�f�rence vers une fonction du c#. 
	///
	/// @param Callback function: reference de la fonction du c#
	///
	////////////////////////////////////////////////////////////////////////
	Callback InterfaceFunctionChangeStateTutoriel = 0;
	__declspec(dllexport) void __cdecl SetCallback(Callback function)
	{
		InterfaceFunctionChangeStateTutoriel = function;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ChangeEditionTutorialState()
	///
	/// Cette fonction appel la m�thode InterfaceFunctionChangeStateTutoriel du c#
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ChangeEditionTutorialState()
	{
		InterfaceFunctionChangeStateTutoriel();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl UpdateEditionTutorialState(int currentState)
	///
	/// Cette fonction assigne l'�tat du tutoriel au mode
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl UpdateEditionTutorialState(int currentState)
	{
		if (FacadeModele::obtenirInstance()->obtenirMode()->obtenirTypeMode() == TUTORIAL_EDITION)
			static_cast<ModeTutorialEdition*>(FacadeModele::obtenirInstance()->obtenirMode())->ModeTutorialEdition::setCurrentTutorialState(currentState);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl UnselectCurrentTool()
	///
	/// Cette fonction d�s�lectionne l'outil utilis� dans le tutoriel du mode
	/// �dition
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl UnselectCurrentTool()
	{
		if (FacadeModele::obtenirInstance()->obtenirMode()->obtenirTypeMode() == TUTORIAL_EDITION)
			static_cast<ModeTutorialEdition*>(FacadeModele::obtenirInstance()->obtenirMode())->ModeTutorialEdition::unselectCurrentTool();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl UnselectAllObjects()
	///
	/// Cette fonction d�s�lectionne tous les objets pr�sent dans la simulation
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl UnselectAllObjects()
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->deselectionnerTout();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl SelectAllTutorialObjects()
	///
	/// Cette fonction permet de s�lectionner tous les objets cr�� lors du tutoriel
	/// du mode �dition
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl SelectAllTutorialObjects()
	{
		if (FacadeModele::obtenirInstance()->obtenirMode()->obtenirTypeMode() == TUTORIAL_EDITION)
			static_cast<ModeTutorialEdition*>(FacadeModele::obtenirInstance()->obtenirMode())->ModeTutorialEdition::selectAllTutorialObjects();
	}

	CallbackForChat Handler = 0;
	__declspec(dllexport) void __cdecl SetCallbackForChat(CallbackForChat handler)
	{
		Handler = handler;
	}

	__declspec(dllexport) void __cdecl TestCallback(std::string message)
	{
		message = message.substr(5);
		const unsigned char* bytes = (const unsigned char*)message.data();
		Handler(bytes, message.size());
	}

	CallbackForNewMap AddNewMap = 0;
	__declspec(dllexport) void __cdecl SetCallbackForNewMap(CallbackForNewMap addNewMap)
	{
		AddNewMap = addNewMap;
	}

	__declspec(dllexport) void __cdecl AddMap(const std::string& name, bool connectionState, int mode, int nbPlayers, int id)
	{
		const unsigned char* bytes = (const unsigned char*)name.data();
		AddNewMap(bytes, name.size(), connectionState, mode, nbPlayers, id);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
