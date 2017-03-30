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
#include <string>
#include <CommCtrl.h>
#include <windowsx.h>
#include <fstream>
#include <sstream>
#include "FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ApplicationSettings::ApplicationSettings()
///
/// Constructeur par d�faut
///
////////////////////////////////////////////////////////////////////////
ApplicationSettings::ApplicationSettings() {
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
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
///	Fonction servant � sauvegarder ou cr�er le fichier d'un profil d'un certain nom.
///
/// @param[in] nomProfil : le nom du profil � sauvegarder
///
////////////////////////////////////////////////////////////////////////
void ApplicationSettings::load() {
	if (!openSaves("rb"))
		return;
	rapidjson::Document doc;
	char readBuffer[65536];
	rapidjson::FileReadStream is(saves_, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	fclose(saves_);

	rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin();

	//Edition Tutorial
	profil_->setEditionTutorialState(itr->value.GetBool());

	//Simulation Tutorial
	profil_->setSimulationTutorialState((++itr)->value.GetBool());

	//Simulation Tutorial
	profil_->setModele((++itr)->value.GetString());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ApplicationSettings::sauvegarder(std::string nomProfil)
///
///	Fonction servant � sauvegarder ou cr�er le fichier d'un profil d'un certain nom.
///
/// @param[in] nomProfil : le nom du profil � sauvegarder
///
////////////////////////////////////////////////////////////////////////
void ApplicationSettings::save() {	
	openSaves("wb");

	char writeBuffer[65536];
	rapidjson::FileWriteStream os(saves_, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	writer.StartObject();
		writer.Key("EditionTutorial");
		writer.Bool(profil_->getSimulationTutorialState());

		writer.Key("SimulationTutorial");
		writer.Bool(profil_->getSimulationTutorialState());

		writer.Key("CarModele");
		writer.String(profil_->getModele().c_str());
	writer.EndObject();

	fclose(saves_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::ouvrirProfil(std::string modeOuverture)
///
///	Fonction permettant d'ouvrir le fichier du profil courant soit en lecture, soit en �criture
///
/// @param[in] modeOuverture : mode lecture ou �criture
///
/// @return Bool Repr�sente si l'ouverture � r�ussi ou non
///
////////////////////////////////////////////////////////////////////////
bool ApplicationSettings::openSaves(std::string modeOuverture) {
	return open(pathToSaves_, modeOuverture, saves_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::ouvrir(std::string nomFichier, std::string modeOuverture, FILE*& fichier)
///
///	Fonction permettant d'ouvrir un fichier soit en lecture, soit en �criture
///
/// @param[in] nomFichier : le nom du fichier � ouvrir avec le chemin vers celui-ci
/// @param[in] modeOuverture : mode lecture ou �criture
/// @param[in] fichier : descripteur de fichier
///
/// @return Bool Repr�sente si l'ouverture � r�ussi ou non
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