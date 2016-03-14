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
#include <fstream>
#include <sstream>
#include "NoeudRobot.h"


ProfilUtilisateur::ProfilUtilisateur(){
	if (!utilitaire::fichierExiste(CHEMIN_PROFIL + DERNIER_PROFIL))
		changerDernierProfil(PROFIL_DEFAUT + EXTENSION_PROFIL);
	
	
	std::ifstream fichierDernierProfilR(CHEMIN_PROFIL + DERNIER_PROFIL);
	std::getline(fichierDernierProfilR, nomProfil_);
	fichierDernierProfilR.close();


    positionsRelatives_ = {{
            NoeudRobot::POSITION_CAPTEUR_DISTANCE_DROITE,
            NoeudRobot::POSITION_CAPTEUR_DISTANCE_CENTRE,
            NoeudRobot::POSITION_CAPTEUR_DISTANCE_GAUCHE
        }};

    anglesRelatifs_ = {{
            NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE,
            NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE,
            NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE
        }};
}


ProfilUtilisateur::ProfilUtilisateur(std::string nomProfil){
	nomProfil_ = nomProfil;
	chargerProfil();
}

ProfilUtilisateur::~ProfilUtilisateur(){

}

void ProfilUtilisateur::changerDernierProfil(std::string nomProfil){
	std::ofstream fichierDernierProfilW(CHEMIN_PROFIL + DERNIER_PROFIL);
	fichierDernierProfilW << nomProfil;
	fichierDernierProfilW.close();
}

bool ProfilUtilisateur::ouvrirProfil(std::string readOrWrite){
	return ouvrir(CHEMIN_PROFIL + nomProfil_, readOrWrite, profil_);
}

bool ProfilUtilisateur::ouvrir(std::string nomFichier, std::string readOrWrite, FILE*& fichier){
	errno_t err;
	err = fopen_s(&fichier, (nomFichier).c_str(), readOrWrite.c_str());
	return err == 0;
}

bool ProfilUtilisateur::sauvegarder(std::string nomProfil){
	nomProfil_ = nomProfil;
	sauvegarder();
	return true;
}

void ProfilUtilisateur::sauvegarder(){
	ouvrirProfil("wb");
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(profil_, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	writer.StartObject();
		writer.Key("nomProfil");
		writer.String(nomProfil_.substr(0,nomProfil_.find_first_of('.')).c_str());

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

		writer.Key("capteursDistance");
		writer.StartArray();
            for each (CapteurDistance capteur in capteursDistance_)
            {
                writer.StartObject();
                capteur.toJSON(writer);
                writer.EndObject();
            }
		writer.EndArray();

		writer.Key("suiveurLigne");
		writer.StartObject();
			suiveurLigne_.toJSON(writer);
		writer.EndObject();

		writer.Key("optionsDebogages");
		writer.StartArray();
			for each (bool option in optionsDebogages_)
			{
				writer.Bool(option);
			}
		writer.EndArray();
	writer.EndObject();
	fclose(profil_);
}

bool ProfilUtilisateur::changerProfil(std::string nomProfil){
	nomProfil_ = nomProfil;

	changerDernierProfil(nomProfil_);

	if (!utilitaire::fichierExiste(CHEMIN_PROFIL + nomProfil_))
		sauvegarder();
	

	comportements_.clear();
	touches_.clear();
	commandes_.clear();

	return chargerProfil();
}

bool ProfilUtilisateur::chargerProfil(){
	if (!ouvrirProfil("rb"))
		return false;
	rapidjson::Document doc;
	char readBuffer[65536];
	rapidjson::FileReadStream is(profil_, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	fclose(profil_);

	rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin();

	this->nomProfil_ = itr->value.GetString();
	std::wstring ws;
	ws.assign(nomProfil_.begin(), nomProfil_.end());
	ComboBox_SelectString(configureHandles.at(PROFIL_CB), 0, ws.c_str());

	itr++;

	const rapidjson::Value& touches = itr->value;

	touches_.resize(touches.Size());

	touches_.at(INVERSER_MODE_CONTROLE) = char(touches[INVERSER_MODE_CONTROLE].GetInt());
	TCHAR* wtouches = new TCHAR[2];
	wtouches[1] = '\0';
	wtouches[0] = touches_.at(INVERSER_MODE_CONTROLE);
	SendMessage(configureHandles.at(MODE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)wtouches);

	touches_.at(AVANCER) = char(touches[AVANCER].GetInt());
	wtouches[0] = touches_.at(AVANCER);
	SendMessage(configureHandles.at(AVANCER_TXT_BOX), WM_SETTEXT, 0, (LPARAM)wtouches);

	touches_.at(RECULER) = char(touches[RECULER].GetInt());
	wtouches[0] = touches_.at(RECULER);
	SendMessage(configureHandles.at(RECULER_TXT_BOX), WM_SETTEXT, 0, (LPARAM)wtouches);

	touches_.at(ROTATION_GAUCHE) = char(touches[ROTATION_GAUCHE].GetInt());
	wtouches[0] = touches_.at(ROTATION_GAUCHE);
	SendMessage(configureHandles.at(ROTATION_GAUCHE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)wtouches);

	touches_.at(ROTATION_DROITE) = char(touches[ROTATION_DROITE].GetInt());
	wtouches[0] = touches_.at(ROTATION_DROITE);
	SendMessage(configureHandles.at(ROTATION_DROITE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)wtouches);

	commandes_.insert(std::make_pair(touches_[INVERSER_MODE_CONTROLE], std::make_unique<CommandeRobot>(INVERSER_MODE_CONTROLE)));
	commandes_.insert(std::make_pair(touches_[AVANCER], std::make_unique<CommandeRobot>(AVANCER, true)));
	commandes_.insert(std::make_pair(touches_[RECULER], std::make_unique<CommandeRobot>(RECULER, true)));
	commandes_.insert(std::make_pair(touches_[ROTATION_GAUCHE], std::make_unique<CommandeRobot>(ROTATION_GAUCHE, true)));
	commandes_.insert(std::make_pair(touches_[ROTATION_DROITE], std::make_unique<CommandeRobot>(ROTATION_DROITE, true)));

	itr++;

	const rapidjson::Value& comportementsJSON = itr->value;

	assert(comportementsJSON.IsArray());

	comportements_.push_back(std::make_unique<ComportementDefaut>(comportementsJSON[DEFAUT]));

	comportements_.push_back(std::make_unique<ComportementSuiviLigne>(comportementsJSON[SUIVIDELIGNE]));
	ComboBox_SetCurSel(configureHandles.at(SUIVI_LIGNE_CB), comportements_.at(SUIVIDELIGNE)->obtenirComportementSuivant());

	comportements_.push_back(std::make_unique<ComportementBalayage>(comportementsJSON[BALAYAGE180]));
	ComboBox_SetCurSel(configureHandles.at(BALAYAGE_CB), comportements_.at(BALAYAGE180)->obtenirComportementSuivant());

	comportements_.push_back(std::make_unique<ComportementDeviation>(comportementsJSON[DEVIATIONVERSLAGAUCHE]));
	ComboBox_SetCurSel(configureHandles.at(DEVIATION_GAUCHE_CB), comportements_.at(DEVIATIONVERSLAGAUCHE)->obtenirComportementSuivant());
	SendMessage(configureHandles.at(DEVIATION_GAUCHE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(comportementsJSON[DEVIATIONVERSLAGAUCHE]["maxAngle"].GetDouble()).substr(0, 5).c_str());

	comportements_.push_back(std::make_unique<ComportementDeviation>(comportementsJSON[DEVIATIONVERSLADROITE]));
	ComboBox_SetCurSel(configureHandles.at(DEVIATION_DROITE_CB), comportements_.at(DEVIATIONVERSLADROITE)->obtenirComportementSuivant());
	SendMessage(configureHandles.at(DEVIATION_DROITE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(comportementsJSON[DEVIATIONVERSLADROITE]["maxAngle"].GetDouble()).substr(0, 5).c_str());

	comportements_.push_back(std::make_unique<ComportementEvitement>(comportementsJSON[EVITEMENTPARLAGAUCHE]));
	ComboBox_SetCurSel(configureHandles.at(EVITEMENT_GAUCHE_CB), comportements_.at(EVITEMENTPARLAGAUCHE)->obtenirComportementSuivant());
	SendMessage(configureHandles.at(EVITEMENT_GAUCHE_ANGLE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(comportementsJSON[EVITEMENTPARLAGAUCHE]["maxAngle"].GetDouble()).substr(0, 5).c_str());
	SendMessage(configureHandles.at(EVITEMENT_GAUCHE_DUREE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(comportementsJSON[EVITEMENTPARLAGAUCHE]["maxTemps"].GetDouble()).substr(0, 5).c_str());

	comportements_.push_back(std::make_unique<ComportementEvitement>(comportementsJSON[EVITEMENTPARLADROITE]));
	ComboBox_SetCurSel(configureHandles.at(EVITEMENT_DROITE_CB), comportements_.at(EVITEMENTPARLADROITE)->obtenirComportementSuivant());
	SendMessage(configureHandles.at(EVITEMENT_DROITE_ANGLE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(comportementsJSON[EVITEMENTPARLADROITE]["maxAngle"].GetDouble()).substr(0, 5).c_str());
	SendMessage(configureHandles.at(EVITEMENT_DROITE_DUREE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(comportementsJSON[EVITEMENTPARLADROITE]["maxTemps"].GetDouble()).substr(0, 5).c_str());

	itr++;

	const rapidjson::Value& capteursDistanceJSON = itr->value;

	assert(capteursDistanceJSON.IsArray());

	//bonne version à utiliser quand merge avec oli
	

	for (unsigned i = 0; i < capteursDistanceJSON.Size(); i++){
		capteursDistance_.at(i) = CapteurDistance(positionsRelatives_.at(i), anglesRelatifs_.at(i), capteursDistanceJSON[i]);
		ComboBox_SetCurSel(configureHandles.at(static_cast<ConfigureControl>(CAPTEUR_DIST_DROIT_CB + i)), 1 - capteursDistanceJSON[i]["estActif"].GetBool());
		ComboBox_SetCurSel(configureHandles.at(static_cast<ConfigureControl>(ZONE_DANGER_DROIT_CB + i)), capteursDistanceJSON[0]["comportementDanger"].GetInt());
		SendMessage(configureHandles.at(static_cast<ConfigureControl>(LARGEUR_DANGER_DROIT_TXT_BOX + i)), WM_SETTEXT, 0, (LPARAM)std::to_wstring(capteursDistanceJSON[i]["distanceDanger"].GetDouble()).substr(0, 5).c_str());
		ComboBox_SetCurSel(configureHandles.at(static_cast<ConfigureControl>(ZONE_SECURITAIRE_DROIT_CB + i)), capteursDistanceJSON[i]["comportementSecuritaire"].GetInt());
		SendMessage(configureHandles.at(static_cast<ConfigureControl>(LARGEUR_SECURITAIRE_DROIT_TXT_BOX + i)), WM_SETTEXT, 0, (LPARAM)std::to_wstring(capteursDistanceJSON[i]["distanceSecuritaire"].GetDouble()).substr(0, 5).c_str());
	}

	itr++;

	suiveurLigne_.assignerActif(itr->value.MemberBegin()->value.GetBool());
	ComboBox_SetCurSel(configureHandles.at(SUIVEUR_LIGNE_CB), 1 - itr->value.MemberBegin()->value.GetBool());

	itr++;

	const rapidjson::Value& optionsDebogagesJSON = itr->value;

	assert(optionsDebogagesJSON.IsArray());

	for (unsigned optionIndex = 0; optionIndex < optionsDebogagesJSON.Size(); optionIndex++)
	{
		optionsDebogages_[optionIndex] = optionsDebogagesJSON[optionIndex].GetBool();
		ComboBox_SetCurSel(configureHandles.at(static_cast<ConfigureControl>(DEBUG_OPTIONS_CB + optionIndex)), 1 - optionsDebogages_[optionIndex]);
	}

	return true;
}

void ProfilUtilisateur::chargerProfilParDefaut(){
	if (!utilitaire::fichierExiste(CHEMIN_PROFIL + nomProfil_)){
		if (!utilitaire::fichierExiste(CHEMIN_PROFIL)){
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wideString = converter.from_bytes(CHEMIN_PROFIL);
			CreateDirectory(wideString.c_str(), NULL);
		}
		touches_.resize(5);
		touches_.at(INVERSER_MODE_CONTROLE) = ' ';
		touches_.at(AVANCER) = 'W';
		touches_.at(RECULER) = 'S';
		touches_.at(ROTATION_GAUCHE) = 'A';
		touches_.at(ROTATION_DROITE) = 'D';

		commandes_.insert(std::make_pair(touches_[INVERSER_MODE_CONTROLE], std::make_unique<CommandeRobot>(INVERSER_MODE_CONTROLE)));
		commandes_.insert(std::make_pair(touches_[AVANCER], std::make_unique<CommandeRobot>(AVANCER, true)));
		commandes_.insert(std::make_pair(touches_[RECULER], std::make_unique<CommandeRobot>(RECULER, true)));
		commandes_.insert(std::make_pair(touches_[ROTATION_GAUCHE], std::make_unique<CommandeRobot>(ROTATION_GAUCHE, true)));
		commandes_.insert(std::make_pair(touches_[ROTATION_DROITE], std::make_unique<CommandeRobot>(ROTATION_DROITE, true)));

		comportements_.push_back(std::make_unique<ComportementDefaut>());
		comportements_.push_back(std::make_unique<ComportementSuiviLigne>(DEFAUT));
		comportements_.push_back(std::make_unique<ComportementBalayage>(DEFAUT));
		comportements_.push_back(std::make_unique<ComportementDeviation>(DEFAUT, 10));
		comportements_.push_back(std::make_unique<ComportementDeviation>(DEFAUT, 10));
		comportements_.push_back(std::make_unique<ComportementEvitement>(DEFAUT, 10 , 3));
		comportements_.push_back(std::make_unique<ComportementEvitement>(DEFAUT, 10, 3));

		capteursDistance_.at(CAPTEUR_DISTANCE_DROITE) = CapteurDistance(NoeudRobot::POSITION_CAPTEUR_DISTANCE_DROITE,
            NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE, true, (TypeComportement)DEFAUT, 25.0, (TypeComportement)DEFAUT, 5.0);
		capteursDistance_.at(CAPTEUR_DISTANCE_CENTRE) = CapteurDistance(NoeudRobot::POSITION_CAPTEUR_DISTANCE_CENTRE,
			NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE, true, (TypeComportement)DEFAUT, 25.0, (TypeComportement)DEFAUT, 5.0);
		capteursDistance_.at(CAPTEUR_DISTANCE_GAUCHE) = CapteurDistance(NoeudRobot::POSITION_CAPTEUR_DISTANCE_GAUCHE,
			NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE, true, (TypeComportement)DEFAUT, 25.0, (TypeComportement)DEFAUT, 5.0);

		suiveurLigne_.assignerActif(true);

		for each (bool option in optionsDebogages_)
		{
			option = true;
		}

		sauvegarder();
	}
	
	chargerProfil();
}

void ProfilUtilisateur::modifierToucheCommande(const uint8_t& touche,const TypeCommande& commande){
	if (!toucheEstUtilise(touche))
	{
		commandes_.erase(touches_[commande]);
		touches_[commande] = touche;
		// Creer la commande dans la map.
		commandes_.insert(std::make_pair(touche, std::make_unique<CommandeRobot>(commande)));
	}
}

void ProfilUtilisateur::assignerComportement(TypeComportement typeComportement, std::unique_ptr<ComportementAbstrait> comportement){
	comportements_.at(typeComportement).swap(comportement);
}

CommandeRobot* ProfilUtilisateur::obtenirCommandeRobot(unsigned char touche) const{
	std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>>::const_iterator it = commandes_.find(touche);
	return (it == commandes_.end()) ? nullptr : (*it).second.get();
}

bool ProfilUtilisateur::toucheEstUtilise(char touche){
	std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>>::const_iterator it = commandes_.find(touche);
	return it != commandes_.end();
}

char ProfilUtilisateur::obtenirToucheCommande(int commande){
	return touches_[commande];
}

void ProfilUtilisateur::setConfigureHandles(HWND handle, ConfigureControl ctrl){
	configureHandles.insert(std::make_pair(ctrl, handle));
}

std::string ProfilUtilisateur::obtenirExtensionProfils(){
	return EXTENSION_PROFIL;
}

std::string ProfilUtilisateur::obtenirCheminProfils(){
	return CHEMIN_PROFIL;
}

void ProfilUtilisateur::supprimerProfil(std::string nomProfil){
	remove((CHEMIN_PROFIL + nomProfil).c_str());
}

std::string ProfilUtilisateur::obtenirNomProfilDefaut(){
	return PROFIL_DEFAUT;
}

void ProfilUtilisateur::assignerCapteurDistance(bool estActif[], TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire){
	for (unsigned i = 0; i < capteursDistance_.size(); i++)
	{
		capteursDistance_.at(i) = CapteurDistance(positionsRelatives_[i], anglesRelatifs_[i], estActif[i], 
                                                  comportementDanger, distanceDanger, 
                                                  comportementSecuritaire, distanceSecuritaire);
	}
}

void ProfilUtilisateur::assignerSuiveurLigne(bool estActif){
	suiveurLigne_.assignerActif(estActif);
}

void ProfilUtilisateur::assignerOptionsDebogages(bool optionsDebogages[]){
	for (unsigned i = 0; i < optionsDebogages_.size(); i++){
		optionsDebogages_.at(i) = optionsDebogages[i];
	}
}
