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


///////////////////////////////////////////////////////////////////////////
/// @class ProfilUtilisateur
/// @brief Classe qui représente le profil d'un utilisateur.
///		   Celle-ci contient toutes options qu'un utilisateur peut changer et sauvegarder.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class ProfilUtilisateur{
	public:
		ProfilUtilisateur(std::string nomProfil, bool* options);
		~ProfilUtilisateur();
		void sauvegarder();
	private:
		std::vector<bool> options_;
		std::string nomProfil_;
		const int NOMBRE_OPTIONS{ 11 };
		FILE* profil;
		const std::string CHEMIN_PROFIL = "./../../Donnees";
		void ouvrirFichierProfil();
};
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////