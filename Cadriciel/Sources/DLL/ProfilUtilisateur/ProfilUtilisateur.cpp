#include "ProfilUtilisateur.h"
#include "rapidjson\writer.h"
#include "rapidjson\reader.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
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
	nomProfil_ = nomProfil;
	chargerProfil();
}

ProfilUtilisateur::~ProfilUtilisateur()
{

}

bool ProfilUtilisateur::ouvrirProfil(){
	errno_t err;
	err = fopen_s(&profil_, (CHEMIN_PROFIL + nomProfil_).c_str(), "ab");
	return err == 0;
}

bool ProfilUtilisateur::sauvegarder(std::string nomProfil){
	nomProfil_ = nomProfil;
	sauvegarder();
	return true;
}

void ProfilUtilisateur::sauvegarder()
{
	ouvrirProfil();
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(profil_, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	writer.StartObject();
	writer.Key("nomProfil");
	writer.String(nomProfil_.c_str());
	writer.Key("comportements");
	writer.StartArray();
	for (std::vector<std::unique_ptr<ComportementAbstrait>>::iterator itr = comportements_.begin(); itr!= comportements_.end(); itr++)
	{
		writer.StartObject();
		(*itr)->toJSON(writer);
		writer.EndObject();
	}
	writer.EndArray();
	writer.EndObject();
	fclose(profil_);
}

bool ProfilUtilisateur::changerProfil(std::string nomProfil){
	nomProfil_ = nomProfil;
	comportements_.clear();
	return chargerProfil();
}

bool ProfilUtilisateur::chargerProfil()
{
	if(!ouvrirProfil())
		return false;
	rapidjson::Document doc;
	char readBuffer[65536];
	rapidjson::FileReadStream is(profil_, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	fclose(profil_);

	rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin();
	this->nomProfil_ = itr->value.GetString();
	itr++;

	const rapidjson::Value& comportements = itr->value;

	assert(comportements.IsArray());

	comportements_.push_back(std::make_unique<ComportementDefaut>(comportements[DEFAUT]));
	comportements_.push_back(std::make_unique<ComportementSuiviLigne>(comportements[SUIVIDELIGNE]));
	comportements_.push_back(std::make_unique<ComportementBalayage>(comportements[BALAYAGE180]));
	comportements_.push_back(std::make_unique<ComportementDeviation>(comportements[DEVIATIONVERSLAGAUCHE]));
	comportements_.push_back(std::make_unique<ComportementDeviation>(comportements[DEVIATIONVERSLADROITE]));
	comportements_.push_back(std::make_unique<ComportementEvitement>(comportements[EVITEMENTPARLAGAUCHE]));
	comportements_.push_back(std::make_unique<ComportementEvitement>(comportements[EVITEMENTPARLADROITE]));
	return true;
}

void ProfilUtilisateur::chargerProfilParDefaut()
{
	struct stat buffer;
	nomProfil_ = "defaut.profil";

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

		comportements_.push_back(std::make_unique<ComportementDefaut>(BALAYAGE180));
		comportements_.push_back(std::make_unique<ComportementSuiviLigne>(BALAYAGE180));
		comportements_.push_back(std::make_unique<ComportementBalayage>(DEVIATIONVERSLAGAUCHE));		
		comportements_.push_back(std::make_unique<ComportementDeviation>(DEFAUT, 50.0));
		comportements_.push_back(std::make_unique<ComportementDeviation>(DEFAUT, 50.0));
		comportements_.push_back(std::make_unique<ComportementEvitement>(DEFAUT, 5.0, 50.0));
		comportements_.push_back(std::make_unique<ComportementEvitement>(DEFAUT, 5.0, 50.0));

		sauvegarder();
		return;
	}

	chargerProfil();

}

void ProfilUtilisateur::modifierToucheCommande(const uint8_t& touche,const TypeCommande& commande)
{
	if (!estUtilise(touche))
	{
		commandes_.erase(touches_[commande]);
		touches_[commande] = touche;
		// Creer la commande dans la map.
		commandes_.insert(std::make_pair(touche, std::make_unique<CommandeRobot>(commande)));
	}
}

void ProfilUtilisateur::assignerComportement(TypeComportement typeComportement, std::unique_ptr<ComportementAbstrait> comportement)
{
	comportements_.at(typeComportement).swap(comportement);
}

CommandeRobot* ProfilUtilisateur::obtenirCommandeRobot(unsigned char touche) const
{
	std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>>::const_iterator it = commandes_.find(touche);
	return (it == commandes_.end()) ? nullptr : (*it).second.get();
}

bool ProfilUtilisateur::estUtilise(char touche)
{
	std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>>::const_iterator it = commandes_.find(touche);
	return it != commandes_.end();
}

char ProfilUtilisateur::obtenirToucheCommande(int commande)
{
	return touches_[commande];
}
