////////////////////////////////////////////////
/// @file   ProfilUtilisateur.h
/// @author Philippe Marcotte
/// @date   2016-02-22
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef __PROFILUTILISATEUR_H__
#define __PROFILUTILISATEUR_H__

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "CommandeRobot.h"
#include "ComportementAbstrait.h"
#include "ConfigureControlEnum.cs"
#include "rapidjson\filereadstream.h"
#include <deque>
#include <Windows.h>
#include "CapteurDistance.h"
#include "SuiveurLigne.h"
#include "NoeudRobot.h"
#include <array>

/// Repr�sente chaque option de d�bogage et permet des obtenirs plus intuitivement
enum optionsDebogagesEnum
{
	ETAT_DEBOGAGE,
	DEBOGAGE_COMPORTEMENTS,
	DEBOGAGE_ECLAIRAGE,
	DEBOGAGE_CAPTEURS
};

///////////////////////////////////////////////////////////////////////////
/// @class ProfilUtilisateur
/// @brief Classe qui repr�sente le profil d'un utilisateur.
///		   Celle-ci contient tous les param�tres contr�lant le robot et servant au d�bogage qu'un utilisateur peut changer et sauvegarder.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class ProfilUtilisateur
{
	friend class ProfilUtilisateurTest;

	public:
		ProfilUtilisateur();

		ProfilUtilisateur(std::string cheminProfil);

		~ProfilUtilisateur();

		void sauvegarder(std::string nomProfil);

		bool changerProfil(std::string nomProfil);

		void assignerComportement(TypeComportement typeComportement, std::unique_ptr<ComportementAbstrait> comportement);

		void modifierToucheCommande(const uint8_t& touche, const TypeCommande& controle);

		void chargerDernierProfil();

		CommandeRobot* obtenirCommandeRobot(unsigned char touche) const;

		bool toucheEstUtilise(char touche);

		char obtenirToucheCommande(int commande);

		void assignerConfigureHandles(HWND handle, ConfigureControl ctrl);

		std::string obtenirExtensionProfils();

		std::string obtenirCheminProfils();

		std::string obtenirNomProfilDefaut();

		std::string obtenirNomDernierProfil();

        inline SuiveurLigne* obtenirSuiveurLigne();
        inline NoeudRobot::ConteneurCapteursDistance* obtenirCapteursDistance();

		void supprimerProfil(std::string nomProfil);

		void assignerCapteurDistance(bool estActif, TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire, int indexCapteur);

		void assignerSuiveurLigne(bool estActif);

		void assignerOptionsDebogages(bool optionsDebogages[]);

		inline int obtenirDureeMaxComportement();
		inline int obtenirDureeMinComportement();

		inline int obtenirLargeurTotalDetectionDistance();

		std::vector<std::unique_ptr<ComportementAbstrait>>* obtenirVecteurComportements();

		bool obtenirOptionDebogage(optionsDebogagesEnum option);

		int* obtenirLimiteParametres();

	private:
		bool creationDossierDonnees();

		void changerDernierProfil(std::string nomProfil);

		void sauvegarder();

		bool ouvrirProfil(std::string readOrWrite);

		bool ouvrir(std::string nomFichier, std::string readOrWrite, FILE*& fichier);

		void creerProfilDefaut();
		
		bool chargerProfil();

		/// Nom du profil courant
		std::string nomProfil_;

		/// Destripteur du fichier profil � sauvegarder ou charger
		FILE* profil_;

		/// Chemin vers le dossier Donnees
		const std::string CHEMIN_PROFIL = "./Donnees/";

		/// Extension d'un fichier de type profil
		const std::string EXTENSION_PROFIL = ".profil";

		/// Nom du profil par d�faut
		const std::string PROFIL_DEFAUT = "defaut";

		/// Nom du fichier contenant le dernier profil charg�
		const std::string DERNIER_PROFIL = "dernier_profil";

		/// Limite maximale pour la dur�e d'un comportement d'�vitement
		const int DUREE_MAX_COMPORTEMENT = 2000;

		/// Limite minimale pour la dur�e d'un comportement d'�vitement
		const int DUREE_MIN_COMPORTEMENT = 0;

		/// Limite totale pour la largeur des zones de danger et s�curitaire
		const int LARGEUR_TOTAL_DETECTION_DISTANCE = 30;

		/// Limite minimale pour la largeur des zones de danger et s�curitaire
		const int LARGEUR_MIN_DETECTION_DISTANCE = 0;

		/// Limite maximale pour un angle de d�viation ou d'�vitement
		const int ANGLE_MAX_COMPORTEMENT = 360;

		/// Limite minimale pour un angle de d�viation ou d'�vitement
		const int ANGLE_MIN_COMPORTEMENT = 0;

		/// Map contenant contenant les handles des contr�les d'interface de la fen�tre Configure
		std::array<HWND, 38> configureHandles;

		/// Tableau contenant les touches utilis�es pour contr�ler le robot.
		std::array<char, 5> touches_;

		/// Pointeur vers un tableau contenant les touches qu'on ne peut pas utiliser pour contr�ler le robot
		const std::array<char, 11>* toucheNonChangeable;

		/// Map associant chaque touche contr�lant le robot � la commande correspondante
		std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>> commandes_;

		/// Vecteur contenant les comportements du robot
		std::vector<std::unique_ptr<ComportementAbstrait>> comportements_;

		/// Conteneur pour les 3 capteurs de distance du robot
        NoeudRobot::ConteneurCapteursDistance capteursDistance_;

		/// Suiveur de ligne du robot
		SuiveurLigne suiveurLigne_;

		/// Tableau contenant la position physique de chaque capteur de distance sur le robot
        std::array<glm::dvec3, NoeudRobot::N_CAPTEURS_DISTANCE> positionsRelatives_;
		/// Tableau contenant l'angle de chaque capteur de distance
        std::array<double, NoeudRobot::N_CAPTEURS_DISTANCE> anglesRelatifs_;

		/// Tableau contenant si les options de d�bogages sont actives ou non et l'�tat de chacune des options
		std::array<bool, 4> optionsDebogages_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline SuiveurLigne* ProfilUtilisateur::obtenirSuiveurLigne()
///
/// Fonction retournant le suiveur de ligne du robot.
///
/// @return SuiveurLigne* Pointeur vers le suiveur de ligne
///
////////////////////////////////////////////////////////////////////////
inline SuiveurLigne* ProfilUtilisateur::obtenirSuiveurLigne()
{
    return &suiveurLigne_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudRobot::ConteneurCapteursDistance* ProfilUtilisateur::obtenirCapteursDistance()
///
/// Fonction retournant le conteneur des capteurs de distance du robot
///
/// @return NoeudRobot::ConteneurCapteursDistance* Pointeur vers le conteneur
///
////////////////////////////////////////////////////////////////////////
inline NoeudRobot::ConteneurCapteursDistance* ProfilUtilisateur::obtenirCapteursDistance()
{
    return &capteursDistance_;
}

#endif // __PROFILUTILISATEUR_H__

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////