///////////////////////////////////////////////////////////////////////////
/// @file   ApplicationSettings.h
/// @author Frederic Gregoire
/// @date   2017-03-29
///
///////////////////////////////////////////////////////////////////////////

#include "ApplicationSettings.h"
#include "rapidjson\writer.h"
#include "rapidjson\reader.h"
#include "rapidjson\filewritestream.h"
#include <sys\stat.h>
#include <windows.h>
#include <locale>
#include <codecvt>
#include "ComportementTypes.h"
#include "utilitaire.h"
#include <string>
#include <CommCtrl.h>
#include <windowsx.h>
#include <fstream>
#include <sstream>

////////////////////////////////////////////////////////////////////////
///
/// @fn ApplicationSettings::ApplicationSettings()
///
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////////////////
ApplicationSettings::ApplicationSettings() {
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ApplicationSettings::~ApplicationSettings()
///
/// Destructeur
///
////////////////////////////////////////////////////////////////////////
ApplicationSettings::~ApplicationSettings(){}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ApplicationSettings::sauvegarder(std::string nomProfil)
///
///	Fonction servant à sauvegarder ou créer le fichier d'un profil d'un certain nom.
///
/// @param[in] nomProfil : le nom du profil à sauvegarder
///
////////////////////////////////////////////////////////////////////////
void ApplicationSettings::load() {

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ApplicationSettings::sauvegarder(std::string nomProfil)
///
///	Fonction servant à sauvegarder ou créer le fichier d'un profil d'un certain nom.
///
/// @param[in] nomProfil : le nom du profil à sauvegarder
///
////////////////////////////////////////////////////////////////////////
void ApplicationSettings::save() {	
	bool success = openSaves("wb");
	if (!success)
	{
		std::ofstream o(pathToSaves_);
		openSaves("wb");
	}

	char writeBuffer[65536];
	rapidjson::FileWriteStream os(saves_, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	writer.StartObject();
		writer.Key("EditionTutorial");
		writer.Bool(false);
	writer.EndObject();

	writer.StartObject();
		writer.Key("SimulationTutorial");
		writer.Bool(false);
	writer.EndObject();

	writer.StartObject();
		writer.Key("CarModele");
		writer.String("robot");
	writer.EndObject();

	fclose(saves_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::ouvrirProfil(std::string modeOuverture)
///
///	Fonction permettant d'ouvrir le fichier du profil courant soit en lecture, soit en écriture
///
/// @param[in] modeOuverture : mode lecture ou écriture
///
/// @return Bool Représente si l'ouverture à réussi ou non
///
////////////////////////////////////////////////////////////////////////
bool ApplicationSettings::openSaves(std::string modeOuverture) {
	return open(pathToSaves_, modeOuverture, saves_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::ouvrir(std::string nomFichier, std::string modeOuverture, FILE*& fichier)
///
///	Fonction permettant d'ouvrir un fichier soit en lecture, soit en écriture
///
/// @param[in] nomFichier : le nom du fichier à ouvrir avec le chemin vers celui-ci
/// @param[in] modeOuverture : mode lecture ou écriture
/// @param[in] fichier : descripteur de fichier
///
/// @return Bool Représente si l'ouverture à réussi ou non
///
////////////////////////////////////////////////////////////////////////
bool ApplicationSettings::open(std::string nomFichier, std::string modeOuverture, FILE*& fichier) {
	errno_t err;
	err = fopen_s(&fichier, (nomFichier).c_str(), modeOuverture.c_str());
	return err == 0;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////