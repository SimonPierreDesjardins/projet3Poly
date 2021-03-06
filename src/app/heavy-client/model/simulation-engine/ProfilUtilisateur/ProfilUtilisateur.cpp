///////////////////////////////////////////////////////////////////////////
/// @file ProfilUtilisateur.cpp
/// @author Philippe Marcotte
/// @date 2016-02-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ProfilUtilisateur.h"
#include "rapidjson\writer.h"
#include "rapidjson\reader.h"
#include "rapidjson\filewritestream.h"
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
#include <fstream>
#include <sstream>
#include <cmath>


const std::array<char, 11> ProfilUtilisateur::toucheNonConfigurable_ = { { '+', '-', '\b', '1', '2', '3', 'J', 'K', 'L', 'B', 'T' } };

////////////////////////////////////////////////////////////////////////
///
/// @fn ProfilUtilisateur::ProfilUtilisateur()
///
/// Constructeur par d�faut
///
////////////////////////////////////////////////////////////////////////
ProfilUtilisateur::ProfilUtilisateur(){
	if (!utilitaire::fichierExiste(CHEMIN_PROFIL + DERNIER_PROFIL)){
		creationDossierDonnees();
		changerDernierProfil(PROFIL_DEFAUT + EXTENSION_PROFIL);
	}
	
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

	pathToMusic_ = EnginSon::obtenirInstance()->getDefaultMusic();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ProfilUtilisateur::~ProfilUtilisateur()
///
/// Destructeur
///
////////////////////////////////////////////////////////////////////////
ProfilUtilisateur::~ProfilUtilisateur(){}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::creationDossierDonnees()
///
///	Fonction servant � v�rifier si le dossier Donnees existe. Dans le cas o� il n'existe pas, on le cr�e.
///
/// @return bool Repr�sente si le dossier existait d�j�
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::creationDossierDonnees(){
	struct stat buffer;
	bool dossierDonneesExiste = stat(CHEMIN_PROFIL.c_str(), &buffer) == 0;
	if (!dossierDonneesExiste){
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wideString = converter.from_bytes(CHEMIN_PROFIL);
		CreateDirectory(CHEMIN_PROFIL.c_str(), NULL);
	}
	return dossierDonneesExiste;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::changerDernierProfil(std::string nomProfil)
///
///	Fonction servant � sauvegarder, dans le fichier dernier_profil, le nom du dernier profil charg�.
///
/// @param[in] nomProfil : le nom du dernier profil charg�
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::changerDernierProfil(std::string nomProfil){
	std::ofstream fichierDernierProfilW(CHEMIN_PROFIL + DERNIER_PROFIL);
	fichierDernierProfilW << nomProfil;
	fichierDernierProfilW.close();
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
bool ProfilUtilisateur::ouvrirProfil(std::string modeOuverture){
	return ouvrir(CHEMIN_PROFIL + nomProfil_, modeOuverture, profil_);
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
bool ProfilUtilisateur::ouvrir(std::string nomFichier, std::string modeOuverture, FILE*& fichier){
	errno_t err;
	err = fopen_s(&fichier, (nomFichier).c_str(), modeOuverture.c_str());
	return err == 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::sauvegarder(std::string nomProfil)
///
///	Fonction servant � sauvegarder ou cr�er le fichier d'un profil d'un certain nom.
///
/// @param[in] nomProfil : le nom du profil � sauvegarder
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::sauvegarder(std::string nomProfil){
	nomProfil_ = nomProfil;
	sauvegarder();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::sauvegarder()
///
///	Fonction servant � sauvegarder, en format JSON, les param�tres du profil courant.
///
////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::changerProfil(std::string nomProfil)
///
///	Fonction servant � charger un nouveau profil. Si le profil n'existe pas, un contenant les param�tres par d�faut est cr�� avec le nom pass� en argument.
///
/// @param[in] nomProfil : le nom du profil que l'on veut charger.
///
/// @return Bool Repr�sente si le profil s'est charg� correctement.
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::changerProfil(std::string nomProfil){
	nomProfil_ = nomProfil;

	changerDernierProfil(nomProfil_);

	if (!utilitaire::fichierExiste(CHEMIN_PROFIL + nomProfil_))
		sauvegarder();
	

	comportements_.clear();
	commandes_.clear();

	return chargerProfil();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::chargerProfil()
///
///	Fonction servant � charger les param�tres d'un profil � partir de son fichier en format JSON.
///
/// @return Bool Repr�sente si le profil s'est charg� correctement.
///
////////////////////////////////////////////////////////////////////////
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

	itr++;

	const rapidjson::Value& touches = itr->value;

	touches_.at(INVERSER_MODE_CONTROLE) = char(touches[INVERSER_MODE_CONTROLE].GetInt());

	touches_.at(AVANCER) = char(touches[AVANCER].GetInt());

	touches_.at(RECULER) = char(touches[RECULER].GetInt());

	touches_.at(ROTATION_GAUCHE) = char(touches[ROTATION_GAUCHE].GetInt());

	touches_.at(ROTATION_DROITE) = char(touches[ROTATION_DROITE].GetInt());

	commandes_.insert(std::make_pair(touches_[INVERSER_MODE_CONTROLE], std::make_unique<CommandeRobot>(INVERSER_MODE_CONTROLE)));
	commandes_.insert(std::make_pair(touches_[AVANCER], std::make_unique<CommandeRobot>(AVANCER, true)));
	commandes_.insert(std::make_pair(touches_[RECULER], std::make_unique<CommandeRobot>(RECULER, true)));
	commandes_.insert(std::make_pair(touches_[ROTATION_GAUCHE], std::make_unique<CommandeRobot>(ROTATION_GAUCHE, true)));
	commandes_.insert(std::make_pair(touches_[ROTATION_DROITE], std::make_unique<CommandeRobot>(ROTATION_DROITE, true)));

	itr++;

	const rapidjson::Value& comportementsJSON = itr->value;

	if (!comportementsJSON.IsArray())
		return false;

	comportements_.push_back(std::make_unique<ComportementDefaut>(comportementsJSON[DEFAUT]));

	comportements_.push_back(std::make_unique<ComportementSuiviLigne>(comportementsJSON[SUIVIDELIGNE]));
	ComboBox_SetCurSel(configureHandles.at(SUIVI_LIGNE_CB), comportements_.at(SUIVIDELIGNE)->obtenirComportementSuivant());

	comportements_.push_back(std::make_unique<ComportementBalayage>(comportementsJSON[BALAYAGE180]));
	ComboBox_SetCurSel(configureHandles.at(BALAYAGE_CB), comportements_.at(BALAYAGE180)->obtenirComportementSuivant());

	comportements_.push_back(std::make_unique<ComportementDeviation>(comportementsJSON[DEVIATIONVERSLAGAUCHE]));
	ComboBox_SetCurSel(configureHandles.at(DEVIATION_GAUCHE_CB), comportements_.at(DEVIATIONVERSLAGAUCHE)->obtenirComportementSuivant());
	SendMessage(configureHandles.at(DEVIATION_GAUCHE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(abs(comportementsJSON[DEVIATIONVERSLAGAUCHE]["maxAngle"].GetDouble())).substr(0, 5).c_str());

	comportements_.push_back(std::make_unique<ComportementDeviation>(comportementsJSON[DEVIATIONVERSLADROITE]));
	ComboBox_SetCurSel(configureHandles.at(DEVIATION_DROITE_CB), comportements_.at(DEVIATIONVERSLADROITE)->obtenirComportementSuivant());
	SendMessage(configureHandles.at(DEVIATION_DROITE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(abs(comportementsJSON[DEVIATIONVERSLADROITE]["maxAngle"].GetDouble())).substr(0, 5).c_str());

	comportements_.push_back(std::make_unique<ComportementEvitement>(comportementsJSON[EVITEMENTPARLAGAUCHE]));
	ComboBox_SetCurSel(configureHandles.at(EVITEMENT_GAUCHE_CB), comportements_.at(EVITEMENTPARLAGAUCHE)->obtenirComportementSuivant());
	SendMessage(configureHandles.at(EVITEMENT_GAUCHE_ANGLE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(abs(comportementsJSON[EVITEMENTPARLAGAUCHE]["maxAngle"].GetDouble())).substr(0, 5).c_str());
	SendMessage(configureHandles.at(EVITEMENT_GAUCHE_DUREE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(comportementsJSON[EVITEMENTPARLAGAUCHE]["maxTemps"].GetDouble()*1000).substr(0, 5).c_str());

	comportements_.push_back(std::make_unique<ComportementEvitement>(comportementsJSON[EVITEMENTPARLADROITE]));
	ComboBox_SetCurSel(configureHandles.at(EVITEMENT_DROITE_CB), comportements_.at(EVITEMENTPARLADROITE)->obtenirComportementSuivant());
	SendMessage(configureHandles.at(EVITEMENT_DROITE_ANGLE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(abs(comportementsJSON[EVITEMENTPARLADROITE]["maxAngle"].GetDouble())).substr(0, 5).c_str());
	SendMessage(configureHandles.at(EVITEMENT_DROITE_DUREE_TXT_BOX), WM_SETTEXT, 0, (LPARAM)std::to_wstring(comportementsJSON[EVITEMENTPARLADROITE]["maxTemps"].GetDouble()*1000).substr(0, 5).c_str());

	itr++;

	const rapidjson::Value& capteursDistanceJSON = itr->value;

	if(!capteursDistanceJSON.IsArray())
		return false;

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

	if(!optionsDebogagesJSON.IsArray())
		return false;

	for (unsigned optionIndex = 0; optionIndex < optionsDebogagesJSON.Size(); optionIndex++)
	{
		optionsDebogages_[optionIndex] = optionsDebogagesJSON[optionIndex].GetBool();
		ComboBox_SetCurSel(configureHandles.at(static_cast<ConfigureControl>(DEBUG_OPTIONS_CB + optionIndex)), 1 - optionsDebogages_[optionIndex]);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::chargerDernierProfil()
///
///	Fonction servant � charger le dernier profil charg� lors de la derni�re utilisation.
/// Si ce profil n'existe pas on charge le profil par d�faut.
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::chargerDernierProfil(){
	if (!utilitaire::fichierExiste(CHEMIN_PROFIL + nomProfil_)){
		nomProfil_ = PROFIL_DEFAUT + EXTENSION_PROFIL;
		changerDernierProfil(PROFIL_DEFAUT + EXTENSION_PROFIL);
		if(!utilitaire::fichierExiste(CHEMIN_PROFIL + PROFIL_DEFAUT + EXTENSION_PROFIL))
			creerProfilDefaut();
	}

	chargerProfil();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::creerProfilDefaut()
///
///	Fonction servant � charger le profil par d�faut sans son fichier JSON.
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::creerProfilDefaut(){
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
	comportements_.push_back(std::make_unique<ComportementEvitement>(DEFAUT, 10, 3));
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::modifierToucheCommande(const uint8_t& touche,const TypeCommande& commande)
///
///	Fonction servant � modifier une des touches associ� � une commande pour contr�ler le robot.
///
/// @param[in] touche : la nouvelle touche
/// @param[in] commande : la commande dont la touche doit �tre modifi�e
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::modifierToucheCommande(const uint8_t& touche,const TypeCommande& commande){
	if (!toucheEstUtilise(touche))
	{
		commandes_.erase(touches_[commande]);
		touches_[commande] = touche;
		// Creer la commande dans la map.
		commandes_.insert(std::make_pair(touche, std::make_unique<CommandeRobot>(commande)));
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::assignerComportement(TypeComportement typeComportement, std::unique_ptr<ComportementAbstrait> comportement)
///
///	Fonction servant � modifier l'un des comportements du robot.
///
/// @param[in] typeComportement : le type du comportement � changer
/// @param[in] comportement : le nouveau comportement
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::assignerComportement(TypeComportement typeComportement, std::unique_ptr<ComportementAbstrait> comportement){
	comportements_.at(typeComportement).swap(comportement);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<std::unique_ptr<ComportementAbstrait>>* ProfilUtilisateur::obtenirVecteurComportements()
///
/// Retourne le pointeur au vecteur des comportements configur�s par l'utilisateur.
///
/// @return std::vector<std::unique_ptr<ComportementAbstrait>>* Pointeur vers le vecteur de comportement.
///
////////////////////////////////////////////////////////////////////////
std::vector<std::unique_ptr<ComportementAbstrait>>* ProfilUtilisateur::obtenirVecteurComportements(){
	return &comportements_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CommandeRobot* ProfilUtilisateur::obtenirCommandeRobot(unsigned char touche) const
///
///	Retourne la commande associ�e � une touche de clavier si elle est bel et bien associ�e � une commande.
///
/// @param[in] touche : la touche entr�e par l'utilisateur�
///
/// @return CommandeRobot* La commande asssoci�e � la touche. nullptr dans le cas o� aucune commande n'est associ�e � la touche entr�e.
///
////////////////////////////////////////////////////////////////////////
CommandeRobot* ProfilUtilisateur::obtenirCommandeRobot(unsigned char touche) const{
	std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>>::const_iterator it = commandes_.find(touche);
	return (it == commandes_.end()) ? nullptr : (*it).second.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::toucheEstUtilise(char touche)
///
///	Fonction servant � savoir si l'on peut associ�e une certaine touche � une commande controlant le robot.
/// Il n'est pas possible d'associer des touches d�j� utilis�es pour d'autres fonctions lors d'une simulation ou d'un test.
///
/// @param[in] touche : la touche � v�rifier
///
/// @return Bool si l'on peut associer cette touche ou non.
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::toucheEstUtilise(char touche){
	bool toucheModifiable = true;
	bool toucheNonModifiable = false;
	bool trouve = false;

	std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>>::const_iterator it = commandes_.find(touche);
	toucheModifiable = it != commandes_.end();

	
	for (int i = 0; i < 11 && !trouve; i++)
	{
		if (toucheNonConfigurable_.at(i) == touche)
		{ 
			toucheNonModifiable = true;
			trouve = true;
		}
	}
	return (toucheModifiable || toucheNonModifiable);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn char ProfilUtilisateur::obtenirToucheCommande(int commande)
///
///	Fonction servant � obtenir la touche associ�e � une commande.
///
/// @param[in] commande : la commande dont l'on veut la touche.
///
/// @return char La touche associ�e � la commande.
///
////////////////////////////////////////////////////////////////////////
char ProfilUtilisateur::obtenirToucheCommande(int commande){
	return touches_[commande];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::assignerConfigureHandles(HWND handle, ConfigureControl ctrl)
///
///	Fonction servant � assigner les handles des contr�les d'interface de la fen�tre Configuration pour ainsi les modifier � partir du mod�le.
///
/// @param[in] handle : la handle d'un des contr�les d'interface
/// @param[in] ctrl : enum repr�sentant le contr�le dont on assigne la handle
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::assignerConfigureHandles(HWND handle, ConfigureControl ctrl){
	configureHandles.at(ctrl) = handle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ProfilUtilisateur::obtenirExtensionProfils()
///
///	Fonction retournant l'extension d'un fichier de type profil
///
/// @return string Extension d'un fichier profil
///
////////////////////////////////////////////////////////////////////////
std::string ProfilUtilisateur::obtenirExtensionProfils(){
	return EXTENSION_PROFIL;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ProfilUtilisateur::obtenirCheminProfils()
///
///	Fonction retournant le chemin vers le dossier Donnees
///
/// @return string Chemin vers le dossier Donnees
///
////////////////////////////////////////////////////////////////////////
std::string ProfilUtilisateur::obtenirCheminProfils(){
	return CHEMIN_PROFIL;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::supprimerProfil(std::string nomProfil)
///
///	Fonction servant � supprimer le fichier d'un certain profil.
///
/// @param[in] nomProfil : le nom du profil � supprimer
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::supprimerProfil(std::string nomProfil){
	remove((CHEMIN_PROFIL + nomProfil).c_str());
	changerDernierProfil(PROFIL_DEFAUT + EXTENSION_PROFIL);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ProfilUtilisateur::obtenirNomProfilDefaut()
///
///	Fonction retournant le nom du profil par d�faut
///
/// @return string Nom du profil par d�faut
///
////////////////////////////////////////////////////////////////////////
std::string ProfilUtilisateur::obtenirNomProfilDefaut(){
	return PROFIL_DEFAUT;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ProfilUtilisateur::obtenirNomDernierProfil()
///
/// Fonction retournant le nom du dernier profil charg�
///
/// @return string Nom du dernier profil charg�
///
////////////////////////////////////////////////////////////////////////
std::string ProfilUtilisateur::obtenirNomDernierProfil(){
	std::ifstream ifs(CHEMIN_PROFIL + DERNIER_PROFIL);
	std::string dernierProfil;
	std::getline(ifs, dernierProfil);
	return dernierProfil.substr(0,dernierProfil.find_first_of('.'));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::assignerCapteurDistance(bool estActif, TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire, int indexCapteur)
///
///	Fonction servant � modifier les capteurs de distance du robot.
///
/// @param[in] estActif : repr�sente si le capteur est actif ou non
/// @param[in] comportementDanger : enum repr�sentant le comportement � adpoter dans une zone de danger
/// @param[in] distanceDanger : la grandeur de la zone de danger
/// @param[in] comportementSecuritaire : enum repr�sentant le comportement � adpoter dans une zone s�curitaire
/// @param[in] distanceSecuritaire : la grandeur de la zone s�curitaire
/// @param[in] indexCapteur : le capteur � modifier (0 � 2)
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::assignerCapteurDistance(bool estActif, TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire, int indexCapteur){
	capteursDistance_.at(indexCapteur) = CapteurDistance(positionsRelatives_[indexCapteur], anglesRelatifs_[indexCapteur], estActif, 
                                                  comportementDanger, distanceDanger, 
                                                  comportementSecuritaire, distanceSecuritaire);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::assignerSuiveurLigne(bool estActif)
///
///	Fonction servant � modifier le suiveur de ligne du robot.
///
/// @param[in] estActif : repr�sente si le suiveur de ligne est actif ou non
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::assignerSuiveurLigne(bool estActif){
	suiveurLigne_.assignerActif(estActif);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::assignerOptionsDebogages(bool optionsDebogages[])
/// 
///	Fonction servant � activer ou d�sactiver les options de d�bogages.
///
/// @param[in] optionsDebogages[] : tableau contenant l'�tat des options de d�bogages
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::assignerOptionsDebogages(bool optionsDebogages[]){
	for (unsigned i = 0; i < optionsDebogages_.size(); i++){
		optionsDebogages_.at(i) = optionsDebogages[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::obtenirOptionDebogage(optionsDebogagesEnum option)
///
///	Fonction retournant l'�tat d'une certaine option de d�bogage
///
/// @param[in] option : enum repr�sentant l'option de d�bogage � retourner
///
/// @return Bool L'�tat de l'option de d�bogage
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::obtenirOptionDebogage(optionsDebogagesEnum option)
{
	if (optionsDebogages_.at(ETAT_DEBOGAGE))
		return optionsDebogages_.at(option);
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int* ProfilUtilisateur::obtenirLimiteParametres()
///
///	Fonction retournant les limites sur les param�tres de comportement du robot
///
/// @return int* Pointeur sur le tableau de limites
///
////////////////////////////////////////////////////////////////////////
int* ProfilUtilisateur::obtenirLimiteParametres(){
	return new int[6] {ANGLE_MIN_COMPORTEMENT, ANGLE_MAX_COMPORTEMENT, DUREE_MIN_COMPORTEMENT, DUREE_MAX_COMPORTEMENT, LARGEUR_MIN_DETECTION_DISTANCE, LARGEUR_TOTAL_DETECTION_DISTANCE};
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::assignerCouleur(int modele, int a, int r, int g, int b)
///
///	Fonction qui assigne les couleurs du modele au tableau en attribut
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::assignerCouleur(int modele, int a, int r, int g, int b) {
	if (modele == WHEELS)
	{
		/*couleurRoues_[0] = (float)a / (float)255;
		couleurRoues_[1] = (float)r / (float)255;
		couleurRoues_[2] = (float)g / (float)255;
		couleurRoues_[3] = (float)b / (float)255;
		estDefautRoues_ = false;*/
		couleurRoues_[0] = a;
		couleurRoues_[1] = r;
		couleurRoues_[2] = g;
		couleurRoues_[3] = b;
	}
	else
	{
		couleurRobot_[0] = a;
		couleurRobot_[1] = r;
		couleurRobot_[2] = g;
		couleurRobot_[3] = b;
		estDefautRobot_ = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int* ProfilUtilisateur::obtenirCouleur(int modele, int index)
///
///	Fonction retournant la couleur du modele a lindex demandee
///
/// @return int* Pointeur sur le tableau des 
///
////////////////////////////////////////////////////////////////////////
int* ProfilUtilisateur::obtenirCouleurs(int modele) {
	if (modele == WHEELS)
	{
		return couleurRoues_;
	}
	else
	{
		return couleurRobot_;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::obtenirCouleurParDefaut(int modele)
///
///	Fonction retournant si le modele possede encore la couleur par defaut
///
/// @return true si la couleur du modele est toujours celle par defaut
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::obtenirCouleurParDefaut(int modele) {
	if (modele == WHEELS)
	{
		return estDefautRoues_;
	}
	else
	{
		return estDefautRobot_;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::setCouleurParDefaut(int modele, bool value)
///
///	Fonction qui attribue la valeur true ou false a lattribut estDefautRoues
///
/// @return
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::setCouleurParDefaut(int modele, bool value) 
{
	if (modele == WHEELS)
	{
		estDefautRoues_ = value;
	}
	else
	{
		estDefautRobot_ = value;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::setModele(std::string modele)
///
///	Fonction qui attribue le modele courant
///
/// @return
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::setModele(std::string modele)
{
	modele_ = modele;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::setCouleurParDefaut(int modele, bool value)
///
///	Fonction qui attribue la valeur true ou false a lattribut estDefautRoues
///
/// @return
///
////////////////////////////////////////////////////////////////////////
std::string ProfilUtilisateur::getModele()
{
	return modele_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ProfilUtilisateur::ajouterPiece()
///
///	Fonction qui incremente l'attribut piecesCollectes
///
/// @return
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::setPiece(int piece)
{
	piecesCollectees = piece;
	if (piece > plusGrandNombrePieces)
	{
		plusGrandNombrePieces = piece;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int ProfilUtilisateur::obtenirMaxPieces()
///
///	Fonction qui retourne l'attribut plusGrandNombrePieces
///
/// @return
///
////////////////////////////////////////////////////////////////////////
int ProfilUtilisateur::obtenirMaxPieces()
{
	return plusGrandNombrePieces;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::obtenirCourseTerminee()
///
///	Fonction qui retourne l'attribut courseTerminee
///
/// @return si la course est fini
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::obtenirCourseTerminee()
{
	return courseTerminee;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::assignerCourseTerminee(bool terminee)
///
///	Fonction qui permet de changer la valeur de courseTerminee
///
/// @return
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::assignerCourseTerminee(bool terminee)
{
	courseTerminee = terminee;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn int ProfilUtilisateur::obtenirPieces()
///
///	Fonction qui retourne l'attribut piecesCollectes
///
/// @return
///
////////////////////////////////////////////////////////////////////////
int ProfilUtilisateur::obtenirPieces()
{
	return piecesCollectees;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ProfilUtilisateur::obtenirCheminVersMusiqueSimulation()
///
///	Fonction qui retourne le chemin a la musique jouer pour simulation
///
/// @return le chemin a la musique jouer pour simulation
///
////////////////////////////////////////////////////////////////////////
std::string ProfilUtilisateur::obtenirCheminVersMusiqueSimulation()
{
	return pathToMusic_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::assignerCheminVersMusiqueSimulation(std::string chemin)
///
///	Fonction qui assigne le chemin a la musique jouer pour simulation
///
/// @args std::string chemin: Path a la musique
/// @return
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::assignerCheminVersMusiqueSimulation(std::string chemin)
{
	pathToMusic_ = chemin;
	EnginSon::obtenirInstance()->setSimulationMusic(chemin);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::getEditionTutorialState() 
///
///	Fonction qui retourne l'�tat du tutoriel edition
///
/// @return bool: �tat du tutoriel edition
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::getEditionTutorialState() 
{
	return completedEditionTutorial_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::setEditionTutorialState(bool completed)
///
///	Fonction qui assigne l'�tat du tutoriel edition
///
/// @args bool compled: etat du tutoriel edition
/// @return
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::setEditionTutorialState(bool completed)
{
	completedEditionTutorial_ = completed;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::getSimulationTutorialState() 
///
///	Fonction qui retourne l'�tat du tutoriel simulation
///
/// @return bool: �tat du tutoriel simulation
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::getSimulationTutorialState()
{
	return completedSimulationTutorial_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::setSimulationTutorialState(bool completed)
///
///	Fonction qui assigne l'�tat du tutoriel simulation
///
/// @args bool compled: etat du tutoriel simulation
/// @return
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::setSimulationTutorialState(bool completed)
{
	completedSimulationTutorial_ = completed;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double ProfilUtilisateur::obtenirRaceTime()
///
///	Fonction retourne le temps de course de lutilisateur
///
/// @args 
/// @return temps de course
///
////////////////////////////////////////////////////////////////////////
double ProfilUtilisateur::obtenirRaceTime()
{
	return raceTime;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double ProfilUtilisateur::obtenirFastestRaceTime()
///
///	Fonction retourne le temps le plus rapide de course de lutilisateur
///
/// @args 
/// @return temps de course
///
////////////////////////////////////////////////////////////////////////
double ProfilUtilisateur::obtenirFastestRaceTime()
{
	return fastestRaceTime;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double ProfilUtilisateur::setRaceTime(double time)
///
///	Fonction set le temps de l<utilisateur ainsi que le plus rapide
///
/// @args temps de course de lutilisateur
/// @return 
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::setRaceTime(double time)
{
	raceTime = time;
	if (time < fastestRaceTime)
	{
		fastestRaceTime = time;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateur::debutDecompte(bool debut)
///
///	Fonction qui set le debut du compte a true ou false
///
/// @args bool qui dit si c<est le debut du decompte
/// @return 
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateur::debutDecompte(bool debut)
{
	debutDecompteCourse = debut;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ProfilUtilisateur::obtenirDebutDecompte()
///
///	Fonction qui retourne si cest le debut du decompte
///
/// @args 
/// @return true ou false que cest le debut du decompte
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateur::obtenirDebutDecompte()
{
	return debutDecompteCourse;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////