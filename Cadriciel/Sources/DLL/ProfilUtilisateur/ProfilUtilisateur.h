////////////////////////////////////////////////
/// @file   ProfilUtilisateur.h
/// @author Philippe Marcotte
/// @date   2016-02-22
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "CommandeRobot.h"
#include "ComportementAbstrait.h"
#include "./../../Enum/ConfigureControlEnum.cs"
#include <deque>
#include <Windows.h>
#include "CapteurDistance.h"
#include "SuiveurLigne.h"

///////////////////////////////////////////////////////////////////////////
/// @class ProfilUtilisateur
/// @brief Classe qui représente le profil d'un utilisateur.
///		   Celle-ci contient toutes options qu'un utilisateur peut changer et sauvegarder.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class ProfilUtilisateur
{
	public:
		ProfilUtilisateur();

		ProfilUtilisateur(std::string nomProfil);

		~ProfilUtilisateur();

		bool sauvegarder(std::string nomProfil);

		bool changerProfil(std::string nomProfil);

		void assignerComportement(TypeComportement typeComportement, std::unique_ptr<ComportementAbstrait> comportement);

		void modifierToucheCommande(const uint8_t& touche, const TypeCommande& controle);

		void chargerProfilParDefaut();

		CommandeRobot* obtenirCommandeRobot(unsigned char touche) const;

		void modifierToucheCommande(char touche, TypeCommande commande);

		bool toucheEstUtilise(char touche);

		char obtenirToucheCommande(int commande);

		void setConfigureHandles(HWND handle, ConfigureControl ctrl);

		std::string obtenirExtensionProfils();

		std::string obtenirCheminProfils();

		std::string obtenirNomProfilDefaut();

		void supprimerProfil(std::string nomProfil);

		

	private:
		void changerDernierProfil(std::string nomProfil);

		void sauvegarder();

		bool ouvrirProfil(std::string readOrWrite);

		bool ouvrir(std::string nomFichier, std::string readOrWrite, FILE*& fichier);

		std::vector<std::unique_ptr<ComportementAbstrait>> comportements_;
		
		bool chargerProfil();
		std::string nomProfil_;
		const int NOMBRE_OPTIONS{ 11 };

		FILE* profil_;

		const std::string CHEMIN_PROFIL = "./../../Donnees/";

		const std::string EXTENSION_PROFIL = ".profil";

		const std::string PROFIL_DEFAUT = "defaut";

		const std::string DERNIER_PROFIL = "dernier_profil";

		std::string dernierProfil;

		std::unordered_map<ConfigureControl, HWND> configureHandles;

		std::vector<char> touches_;
		// Utilisation d'une unordered map pour un temps d'acces constant.
		std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>> commandes_;

		std::vector<CapteurDistance> capteursDistance_;

		SuiveurLigne suiveurLigne_;
};


////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////