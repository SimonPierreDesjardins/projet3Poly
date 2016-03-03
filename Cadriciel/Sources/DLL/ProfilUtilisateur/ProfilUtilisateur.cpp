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
#include "utilitaire.h"
#include <string>
#include <CommCtrl.h>
#include <windowsx.h>
#include <atlstr.h>


ProfilUtilisateur::ProfilUtilisateur()
{
}


ProfilUtilisateur::ProfilUtilisateur(std::string nomProfil)
{
	nomProfil_ = nomProfil;
	chargerProfil();
}

ProfilUtilisateur::~ProfilUtilisateur()
{

}

bool ProfilUtilisateur::ouvrirProfil(std::string readOrWrite){
	errno_t err;
	err = fopen_s(&profil_, (CHEMIN_PROFIL + nomProfil_ + EXTENSION_PROFIL).c_str(), readOrWrite.c_str());
	return err == 0;
}

bool ProfilUtilisateur::sauvegarder(std::string nomProfil){
	nomProfil_ = nomProfil;
	sauvegarder();
	return true;
}

void ProfilUtilisateur::sauvegarder()
{
	ouvrirProfil("wb");
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(profil_, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	writer.StartObject();
		writer.Key("nomProfil");
		writer.String(nomProfil_.c_str());

		writer.Key("touches");
		writer.StartArray();
			for each (char touche in touches_)
			{
				writer.Int(touche);
			}
		writer.EndArray();

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
	if(!ouvrirProfil("rb"))
		return false;
	rapidjson::Document doc;
	char readBuffer[65536];
	rapidjson::FileReadStream is(profil_, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	fclose(profil_);
	rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin();
	this->nomProfil_ = itr->value.GetString();
	itr++;

	const rapidjson::Value& touches = itr->value;

	TCHAR texte[2];
	texte[1] = '\0';
	touches_.clear();
	int size = touches.Size();
	touches_.resize(size);
	texte[0] = touches_.at(INVERSER_MODE_CONTROLE) = char(touches[INVERSER_MODE_CONTROLE].GetInt());
	SendMessage(configureHandles.at(MODE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)texte);

	texte[0] = touches_.at(AVANCER) = char(touches[AVANCER].GetInt());
	SendMessage(configureHandles.at(AVANCER_TXT_BOX), WM_SETTEXT, 0, (LPARAM)texte);

	texte[0] = touches_.at(RECULER) = char(touches[RECULER].GetInt());
	SendMessage(configureHandles.at(RECULER_TXT_BOX), WM_SETTEXT, 0, (LPARAM)texte);

	texte[0] = touches_.at(ROTATION_GAUCHE) = char(touches[ROTATION_GAUCHE].GetInt());
	SendMessage(configureHandles.at(ROTATION_GAUCHE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)texte);

	texte[0] = touches_.at(ROTATION_DROITE) = char(touches[ROTATION_DROITE].GetInt());
	SendMessage(configureHandles.at(ROTATION_DROITE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)texte);
	/*for (size_t i = 0; i < size; i++)
	{
		touches_.at(i) = unsigned char(touches[i].GetInt());
		texte[0] = touches_[i];
		SendMessage(configureHandles.at(i), WM_SETTEXT, 0, (LPARAM)texte);
	}*/

	itr++;
	const rapidjson::Value& comportements = itr->value;

	assert(comportements.IsArray());

	comportements_.push_back(std::make_unique<ComportementDefaut>(comportements[DEFAUT]));

	comportements_.push_back(std::make_unique<ComportementSuiviLigne>(comportements[SUIVIDELIGNE]));
	ComboBox_SetCurSel(configureHandles.at(SUIVI_LIGNE_CB), comportements_.at(SUIVIDELIGNE)->obtenirComportementSuivant());

	comportements_.push_back(std::make_unique<ComportementBalayage>(comportements[BALAYAGE180]));
	ComboBox_SetCurSel(configureHandles.at(BALAYAGE_CB), comportements_.at(BALAYAGE180)->obtenirComportementSuivant());

	comportements_.push_back(std::make_unique<ComportementDeviation>(comportements[DEVIATIONVERSLAGAUCHE]));
	ComboBox_SetCurSel(configureHandles.at(DEVIATION_GAUCHE_CB), comportements_.at(DEVIATIONVERSLAGAUCHE)->obtenirComportementSuivant());
	std::string stringTmp = std::to_string(comportements[DEVIATIONVERSLAGAUCHE]["maxAngle"].GetDouble()).substr(0, 5);
	TCHAR * tcharTmp = new TCHAR[stringTmp.length() + 1];
	tcharTmp[stringTmp.length()] = 0;
	std::copy(stringTmp.begin(), stringTmp.end(), tcharTmp);
	SendMessage(configureHandles.at(DEVIATION_GAUCHE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)tcharTmp);

	comportements_.push_back(std::make_unique<ComportementDeviation>(comportements[DEVIATIONVERSLADROITE]));
	ComboBox_SetCurSel(configureHandles.at(DEVIATION_DROITE_CB), comportements_.at(DEVIATIONVERSLADROITE)->obtenirComportementSuivant());
	stringTmp = std::to_string(comportements[DEVIATIONVERSLADROITE]["maxAngle"].GetDouble()).substr(0, 5);
	tcharTmp = new TCHAR[stringTmp.length() + 1];
	tcharTmp[stringTmp.length()] = 0;
	std::copy(stringTmp.begin(), stringTmp.end(), tcharTmp);
	SendMessage(configureHandles.at(DEVIATION_DROITE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)tcharTmp);

	comportements_.push_back(std::make_unique<ComportementEvitement>(comportements[EVITEMENTPARLAGAUCHE]));
	ComboBox_SetCurSel(configureHandles.at(EVITEMENT_GAUCHE_CB), comportements_.at(EVITEMENTPARLAGAUCHE)->obtenirComportementSuivant());
	stringTmp = std::to_string(comportements[EVITEMENTPARLAGAUCHE]["maxAngle"].GetDouble()).substr(0, 5);
	tcharTmp = new TCHAR[stringTmp.length() + 1];
	tcharTmp[stringTmp.length()] = 0;
	std::copy(stringTmp.begin(), stringTmp.end(), tcharTmp);
	SendMessage(configureHandles.at(EVITEMENT_GAUCHE_ANGLE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)tcharTmp);
	stringTmp = std::to_string(comportements[EVITEMENTPARLAGAUCHE]["maxTemps"].GetDouble()).substr(0, 5);
	tcharTmp = new TCHAR[stringTmp.length() + 1];
	tcharTmp[stringTmp.length()] = 0;
	std::copy(stringTmp.begin(), stringTmp.end(), tcharTmp);
	SendMessage(configureHandles.at(EVITEMENT_GAUCHE_DUREE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)tcharTmp);

	comportements_.push_back(std::make_unique<ComportementEvitement>(comportements[EVITEMENTPARLADROITE]));
	ComboBox_SetCurSel(configureHandles.at(EVITEMENT_DROITE_CB), comportements_.at(EVITEMENTPARLADROITE)->obtenirComportementSuivant());
	stringTmp = std::to_string(comportements[EVITEMENTPARLADROITE]["maxAngle"].GetDouble());
	tcharTmp = new TCHAR[stringTmp.length() + 1];
	tcharTmp[stringTmp.length()] = 0;
	std::copy(stringTmp.begin(), stringTmp.end(), tcharTmp);
	SendMessage(configureHandles.at(EVITEMENT_DROITE_ANGLE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)tcharTmp);
	stringTmp = std::to_string(comportements[EVITEMENTPARLADROITE]["maxTemps"].GetDouble());
	tcharTmp = new TCHAR[stringTmp.length() + 1];
	tcharTmp[stringTmp.length()] = 0;
	std::copy(stringTmp.begin(), stringTmp.end(), tcharTmp);
	SendMessage(configureHandles.at(EVITEMENT_DROITE_DUREE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)tcharTmp);

	delete [] tcharTmp;

	return true;
}

void ProfilUtilisateur::chargerProfilParDefaut()
{
	struct stat buffer;
	nomProfil_ = "défaut";

	if (!utilitaire::fichierExiste(CHEMIN_PROFIL + nomProfil_ + EXTENSION_PROFIL)) {
		if (stat(CHEMIN_PROFIL.c_str(), &buffer) != 0){
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wideString = converter.from_bytes(CHEMIN_PROFIL);
			CreateDirectory(wideString.c_str(), NULL);
		}

		touches_.resize(5);
		touches_[INVERSER_MODE_CONTROLE] = ' ';
		touches_[AVANCER] = 'w';
		touches_[RECULER] = 'w';
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

void ProfilUtilisateur::setConfigureHandles(HWND handle, ConfigureControl ctrl){
	configureHandles.insert(std::make_pair(ctrl, handle));
}
