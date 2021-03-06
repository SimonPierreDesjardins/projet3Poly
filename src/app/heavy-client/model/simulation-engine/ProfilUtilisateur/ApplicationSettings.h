////////////////////////////////////////////////
/// @file   ApplicationSettings.h
/// @author Frederic Gregoire
/// @date   2017-03-29
///
////////////////////////////////////////////////
#ifndef __APPLICATION_SETTINGS_H__
#define __APPLICATION_SETTINGS_H__

#include <memory>
#include <string>
#include "rapidjson\filereadstream.h"
#include <Windows.h>
#include "ProfilUtilisateur.h"


///////////////////////////////////////////////////////////////////////////
/// @class ApplicationSettings
/// @brief Classe qui repr�sente les parametres sauvegarder par notre application.
///
/// @author Frederic Gregoire
/// @date 2017-03-29
///////////////////////////////////////////////////////////////////////////
class ApplicationSettings
{
	public:
		ApplicationSettings(ProfilUtilisateur* profil);
		~ApplicationSettings();

		void load();
		void save();

		bool openSaves(std::string modeOuverture);
		bool open(std::string nomFichier, std::string modeOuverture, FILE*& fichier);

	private:
		/// Destripteur du fichier profil � sauvegarder ou charger
		FILE* saves_;
		/// Le profil utilisateur.
		ProfilUtilisateur* profil_{ nullptr };
		/// Chemin vers le fichier de sauvegarde
		const std::string pathToSaves_ = "./Donnees/ApplicationSaves.save";
};

#endif // __APPLICATION_SETTINGS_H__

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////