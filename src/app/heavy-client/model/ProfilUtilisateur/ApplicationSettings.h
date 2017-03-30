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
#include "ConfigureControlEnum.cs"
#include "rapidjson\filereadstream.h"
#include <Windows.h>


///////////////////////////////////////////////////////////////////////////
/// @class ApplicationSettings
/// @brief Classe qui représente les parametres sauvegarder par notre application.
///
/// @author Frederic Gregoire
/// @date 2017-03-29
///////////////////////////////////////////////////////////////////////////
class ApplicationSettings
{
	public:
		ApplicationSettings();

		~ApplicationSettings();

		void load();
		void save();

		bool openSaves(std::string modeOuverture);
		bool open(std::string nomFichier, std::string modeOuverture, FILE*& fichier);

	private:
		/// Destripteur du fichier profil à sauvegarder ou charger
		FILE* saves_;

		/// Chemin vers le fichier de sauvegarde
		const std::string pathToSaves_ = "./Donnees/ApplicationSaves.save";
};

#endif // __APPLICATION_SETTINGS_H__

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////