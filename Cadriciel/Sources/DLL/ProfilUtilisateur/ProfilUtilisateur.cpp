#include "ProfilUtilisateur.h"
#include "rapidjson\writer.h"
#include "rapidjson\reader.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
#include "CommandeRobot.h"
#include <sys\stat.h>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <iostream>
#include "ComportementTypes.h"

ProfilUtilisateur::ProfilUtilisateur()
{
	chargerProfilParDefaut();
}


ProfilUtilisateur::ProfilUtilisateur(std::string nomProfil)
{
	options_.push_back(std::make_unique<ComportementSuiviLigne>());
	options_.push_back(std::make_unique<ComportementBalayage>());
	options_.push_back(std::make_unique<ComportementDeviation>());
	options_.push_back(std::make_unique<ComportementDeviation>());
	options_.push_back(std::make_unique<ComportementEvitement>());
	options_.push_back(std::make_unique<ComportementEvitement>());
	nomProfil_ = nomProfil;
	chargerProfilParDefaut();
}

ProfilUtilisateur::~ProfilUtilisateur()
{
	//delete profil_;
}

void ProfilUtilisateur::sauvegarder()
{
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(profil_, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer();


}

void ProfilUtilisateur::ouvrirFichierProfil(std::string nomProfil){
	nomProfil_ = nomProfil;
	ouvrirFichierProfil();
}

void ProfilUtilisateur::ouvrirFichierProfil()
{
	errno_t err;
	if (err = fopen_s(&profil_, (CHEMIN_PROFIL + nomProfil_).c_str(), "ab") != 0){
		std::cout << "Erreur lors de l'ouverture du fichier profil : " << err << std::endl;
	}
}

void ProfilUtilisateur::chargerProfilParDefaut()
{
	struct stat buffer;
	nomProfil_ = "profil_par_defaut.json";
	if (stat((CHEMIN_PROFIL + nomProfil_).c_str(), &buffer) != 0) {
		if (stat(CHEMIN_PROFIL.c_str(), &buffer) != 0){
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wideString = converter.from_bytes(CHEMIN_PROFIL);
			CreateDirectory(wideString.c_str(), NULL);
		}
		touches_.resize(5);
		touches_[INVERSER_MODE_CONTROLE] = ' ';
		touches_[AVANCER] = 'w';
		touches_[RECULER] = 's';
		touches_[ROTATION_GAUCHE] = 'a';
		touches_[ROTATION_DROITE] = 'd';

		commandes_.insert(std::make_pair(touches_[INVERSER_MODE_CONTROLE], std::make_unique<CommandeRobot>(INVERSER_MODE_CONTROLE)));
		commandes_.insert(std::make_pair(touches_[AVANCER], std::make_unique<CommandeRobot>(AVANCER)));
		commandes_.insert(std::make_pair(touches_[RECULER], std::make_unique<CommandeRobot>(RECULER)));
		commandes_.insert(std::make_pair(touches_[ROTATION_GAUCHE], std::make_unique<CommandeRobot>(ROTATION_GAUCHE)));
		commandes_.insert(std::make_pair(touches_[ROTATION_DROITE], std::make_unique<CommandeRobot>(ROTATION_DROITE)));

		sauvegarder();
		return;
	}

	ouvrirFichierProfil();
}

void ProfilUtilisateur::modifierToucheCommande(const unsigned char& touche, const TypeCommande& commande)
{
	// Mettre a jour la touche dans la table de commandes.
	commandes_.erase(touches_.at(commande));
	touches_[commande] = touche;
	// Creer la commande dans la map.
	commandes_.insert(std::make_pair(touche, std::make_unique<CommandeRobot>(commande)));
}