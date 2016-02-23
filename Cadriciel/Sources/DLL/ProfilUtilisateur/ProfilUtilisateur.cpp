#include "ProfilUtilisateur.h"
#include "rapidjson\writer.h"
#include "rapidjson\reader.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
#include "CommandeRobot.h"

ProfilUtilisateur::ProfilUtilisateur()
{
	chargerProfilParDefaut();
}


ProfilUtilisateur::ProfilUtilisateur(std::string nomProfil, bool* options)
{
	options_ = std::vector<bool>(options, options + NOMBRE_OPTIONS*sizeof(bool));
	nomProfil_ = nomProfil;
	chargerProfilParDefaut();
}

ProfilUtilisateur::~ProfilUtilisateur()
{
	delete profil_;
}

void ProfilUtilisateur::sauvegarder()
{
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(profil_, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer();
}

void ProfilUtilisateur::ouvrirFichierProfil()
{
	profil_ = fopen((CHEMIN_PROFIL + nomProfil_).c_str(), "ab");
}


void ProfilUtilisateur::chargerProfilParDefaut()
{
	commandes_.insert(std::make_pair(32, std::make_unique<CommandeRobot>(INVERSER_MODE_CONTROLE)));
	commandes_.insert(std::make_pair(87, std::make_unique<CommandeRobot>(AVANCER)));
	commandes_.insert(std::make_pair(83, std::make_unique<CommandeRobot>(RECULER)));
	commandes_.insert(std::make_pair(65, std::make_unique<CommandeRobot>(ROTATION_GAUCHE)));
	commandes_.insert(std::make_pair(68, std::make_unique<CommandeRobot>(ROTATION_DROITE)));

	touches_.resize(5);
	touches_[INVERSER_MODE_CONTROLE] = 32;
	touches_[AVANCER] = 87;
	touches_[RECULER] = 83;
	touches_[ROTATION_GAUCHE] = 65;
	touches_[ROTATION_DROITE] = 68;
}

void ProfilUtilisateur::modifierToucheCommande(const unsigned char& touche, const TypeCommande& commande)
{
	// Mettre a jour la touche dans la table de commandes.
	commandes_.erase(touches_[commande]);
	touches_[commande] = touche;
	// Creer la commande dans la map.
	commandes_.insert(std::make_pair(touche, std::make_unique<CommandeRobot>(commande)));
}