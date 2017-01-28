////////////////////////////////////////////////////////////////////////////////////
/// @file ProfilUtilisateurTest.cpp
/// @author Philippe Marcotte
/// @date 2016-03-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////
#include "ProfilUtilisateurTest.h"
#include "ComportementTypes.h"
#include <sys\stat.h>
#include <locale>
#include <codecvt>

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ProfilUtilisateurTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateurTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateurTest::setUp(){
	profilCorrect = new ProfilUtilisateur();
	profilCorrect->nomProfil_ = nomProfilTest;

	profilCorrect->touches_.at(INVERSER_MODE_CONTROLE) = ' ';
	profilCorrect->touches_.at(AVANCER) = 'W';
	profilCorrect->touches_.at(RECULER) = 'S';
	profilCorrect->touches_.at(ROTATION_GAUCHE) = 'A';
	profilCorrect->touches_.at(ROTATION_DROITE) = 'D';

	profilCorrect->commandes_.insert(std::make_pair(profilCorrect->touches_[INVERSER_MODE_CONTROLE], std::make_unique<CommandeRobot>(INVERSER_MODE_CONTROLE)));
	profilCorrect->commandes_.insert(std::make_pair(profilCorrect->touches_[AVANCER], std::make_unique<CommandeRobot>(AVANCER, true)));
	profilCorrect->commandes_.insert(std::make_pair(profilCorrect->touches_[RECULER], std::make_unique<CommandeRobot>(RECULER, true)));
	profilCorrect->commandes_.insert(std::make_pair(profilCorrect->touches_[ROTATION_GAUCHE], std::make_unique<CommandeRobot>(ROTATION_GAUCHE, true)));
	profilCorrect->commandes_.insert(std::make_pair(profilCorrect->touches_[ROTATION_DROITE], std::make_unique<CommandeRobot>(ROTATION_DROITE, true)));

	profilCorrect->comportements_.push_back(std::make_unique<ComportementDefaut>());
	profilCorrect->comportements_.push_back(std::make_unique<ComportementSuiviLigne>(DEFAUT));
	profilCorrect->comportements_.push_back(std::make_unique<ComportementBalayage>(DEFAUT));
	profilCorrect->comportements_.push_back(std::make_unique<ComportementDeviation>(DEFAUT, 10));
	profilCorrect->comportements_.push_back(std::make_unique<ComportementDeviation>(DEFAUT, 10));
	profilCorrect->comportements_.push_back(std::make_unique<ComportementEvitement>(DEFAUT, 10, 3));
	profilCorrect->comportements_.push_back(std::make_unique<ComportementEvitement>(DEFAUT, 10, 3));

	profilCorrect->capteursDistance_.at(CAPTEUR_DISTANCE_DROITE) = CapteurDistance(NoeudRobot::POSITION_CAPTEUR_DISTANCE_DROITE,
		NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE, true, (TypeComportement)DEFAUT, 25.0, (TypeComportement)DEFAUT, 5.0);
	profilCorrect->capteursDistance_.at(CAPTEUR_DISTANCE_CENTRE) = CapteurDistance(NoeudRobot::POSITION_CAPTEUR_DISTANCE_CENTRE,
		NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE, true, (TypeComportement)DEFAUT, 25.0, (TypeComportement)DEFAUT, 5.0);
	profilCorrect->capteursDistance_.at(CAPTEUR_DISTANCE_GAUCHE) = CapteurDistance(NoeudRobot::POSITION_CAPTEUR_DISTANCE_GAUCHE,
		NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE, true, (TypeComportement)DEFAUT, 25.0, (TypeComportement)DEFAUT, 5.0);

	profilCorrect->suiveurLigne_.assignerActif(true);

	for each (bool option in profilCorrect->optionsDebogages_)
	{
		option = true;
	}

	profilCorrect->sauvegarder();

	profilTest = new ProfilUtilisateur();
	profilTest->nomProfil_ = nomProfilTest;
	chargerProfil(profilTest);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateurTest::tearDown(){
	remove((profilCorrect->CHEMIN_PROFIL + nomProfilTest).c_str());

	delete profilCorrect;
	delete profilTest;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateurTest::testChargerProfil()
///
///	Vérifie que chaques attributs chargés à partir du fichier JSON dans profilTest 
/// correspondent aux attributs de profilCorrect.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateurTest::testChargerProfil(){
	for (size_t i = 0; i < profilCorrect->touches_.size(); i++)
	{
		CPPUNIT_ASSERT(profilCorrect->touches_.at(i) == profilTest->touches_.at(i));
		CPPUNIT_ASSERT(profilCorrect->commandes_.at(profilCorrect->touches_.at(i))->obtenirTypeCommande() == profilTest->commandes_.at(profilTest->touches_.at(i))->obtenirTypeCommande());
	}

	for (size_t i = 0; i < profilCorrect->comportements_.size(); i++)
	{
		CPPUNIT_ASSERT(profilCorrect->comportements_.at(i)->obtenirNomComportement() == profilTest->comportements_.at(i)->obtenirNomComportement());
		CPPUNIT_ASSERT(profilCorrect->comportements_.at(i)->obtenirComportementSuivant() == profilTest->comportements_.at(i)->obtenirComportementSuivant());
	}

	ComportementDeviation* comportementDeviationGaucheCorrect = static_cast<ComportementDeviation*>(profilCorrect->comportements_.at(DEVIATIONVERSLAGAUCHE).release());
	ComportementDeviation* comportementDeviationGaucheTest = static_cast<ComportementDeviation*>(profilTest->comportements_.at(DEVIATIONVERSLAGAUCHE).release());

	CPPUNIT_ASSERT(comportementDeviationGaucheCorrect->obtenirMaxAngle() == comportementDeviationGaucheTest->obtenirMaxAngle());

	delete comportementDeviationGaucheCorrect;
	delete comportementDeviationGaucheTest;

	ComportementDeviation* comportementDeviationDroiteCorrect = static_cast<ComportementDeviation*>(profilCorrect->comportements_.at(DEVIATIONVERSLADROITE).release());
	ComportementDeviation* comportementDeviationDroiteTest = static_cast<ComportementDeviation*>(profilTest->comportements_.at(DEVIATIONVERSLADROITE).release());

	CPPUNIT_ASSERT(comportementDeviationDroiteCorrect->obtenirMaxAngle() == comportementDeviationDroiteTest->obtenirMaxAngle());

	delete comportementDeviationDroiteCorrect;
	delete comportementDeviationDroiteTest;

	ComportementEvitement* comportementEvitementGaucheCorrect = static_cast<ComportementEvitement*>(profilCorrect->comportements_.at(EVITEMENTPARLAGAUCHE).release());
	ComportementEvitement* comportementEvitementGaucheTest = static_cast<ComportementEvitement*>(profilTest->comportements_.at(EVITEMENTPARLAGAUCHE).release());

	CPPUNIT_ASSERT(comportementEvitementGaucheCorrect->obtenirMaxAngle() == comportementEvitementGaucheTest->obtenirMaxAngle());
	CPPUNIT_ASSERT(comportementEvitementGaucheCorrect->obtenirMaxTemps() == comportementEvitementGaucheTest->obtenirMaxTemps());

	delete comportementEvitementGaucheCorrect;
	delete comportementEvitementGaucheTest;

	ComportementEvitement* comportementEvitementDroiteCorrect = static_cast<ComportementEvitement*>(profilCorrect->comportements_.at(EVITEMENTPARLADROITE).release());
	ComportementEvitement* comportementEvitementDroiteTest = static_cast<ComportementEvitement*>(profilTest->comportements_.at(EVITEMENTPARLADROITE).release());

	CPPUNIT_ASSERT(comportementEvitementDroiteCorrect->obtenirMaxAngle() == comportementEvitementDroiteTest->obtenirMaxAngle());
	CPPUNIT_ASSERT(comportementEvitementDroiteCorrect->obtenirMaxTemps() == comportementEvitementDroiteTest->obtenirMaxTemps());

	delete comportementEvitementDroiteCorrect;
	delete comportementEvitementDroiteTest;

	for (size_t i = 0; i < profilCorrect->capteursDistance_.size(); i++)
	{
		CPPUNIT_ASSERT(profilCorrect->capteursDistance_.at(i).obtenirEstActif() == profilTest->capteursDistance_.at(i).obtenirEstActif());
		CPPUNIT_ASSERT(profilCorrect->capteursDistance_.at(i).obtenirComportementZoneDanger() == profilTest->capteursDistance_.at(i).obtenirComportementZoneDanger());
		CPPUNIT_ASSERT(profilCorrect->capteursDistance_.at(i).obtenirComportementZoneSecuritaire() == profilTest->capteursDistance_.at(i).obtenirComportementZoneSecuritaire());
		CPPUNIT_ASSERT(profilCorrect->capteursDistance_.at(i).obtenirLargeurDanger() == profilTest->capteursDistance_.at(i).obtenirLargeurDanger());
		CPPUNIT_ASSERT(profilCorrect->capteursDistance_.at(i).obtenirLargeurSecuritaire() == profilTest->capteursDistance_.at(i).obtenirLargeurSecuritaire());
	}

	CPPUNIT_ASSERT(profilCorrect->suiveurLigne_.obtenirEstActif() == profilTest->suiveurLigne_.obtenirEstActif());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateurTest::testAssignerTouche()
///
///	Vérifie que la modification d'une touche associée à une commande robot s'effectue correctement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProfilUtilisateurTest::testAssignerTouche(){
	uint8_t touche = 'Y';

	profilCorrect->modifierToucheCommande(touche, AVANCER);

	CPPUNIT_ASSERT(profilCorrect->touches_.at(AVANCER) == touche);

	CPPUNIT_ASSERT(profilCorrect->commandes_.at(touche)->obtenirTypeCommande() == AVANCER);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProfilUtilisateurTest::chargerProfil(ProfilUtilisateur* profil)
///
///	Version modifiée de la fonction chargerProfil() de ProfilUtilisateur. 
/// Celle-ci ne fait pas appel à de fonctions de la librairie Win32, car c'est inutile dans le contexte des tests.
///
/// @param[in] profil : Pointeur vers le profil dans lequel charger le fichier test.
///
////////////////////////////////////////////////////////////////////////
bool ProfilUtilisateurTest::chargerProfil(ProfilUtilisateur* profil){
	if (!profil->ouvrirProfil("rb"))
		return false;
	rapidjson::Document doc;
	char readBuffer[65536];
	rapidjson::FileReadStream is(profil->profil_, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	fclose(profil->profil_);

	rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin();

	profil->nomProfil_ = itr->value.GetString();

	itr++;

	const rapidjson::Value& touches = itr->value;

	profil->touches_.at(INVERSER_MODE_CONTROLE) = char(touches[INVERSER_MODE_CONTROLE].GetInt());

	profil->touches_.at(AVANCER) = char(touches[AVANCER].GetInt());

	profil->touches_.at(RECULER) = char(touches[RECULER].GetInt());

	profil->touches_.at(ROTATION_GAUCHE) = char(touches[ROTATION_GAUCHE].GetInt());

	profil->touches_.at(ROTATION_DROITE) = char(touches[ROTATION_DROITE].GetInt());

	profil->commandes_.insert(std::make_pair(profil->touches_[INVERSER_MODE_CONTROLE], std::make_unique<CommandeRobot>(INVERSER_MODE_CONTROLE)));
	profil->commandes_.insert(std::make_pair(profil->touches_[AVANCER], std::make_unique<CommandeRobot>(AVANCER, true)));
	profil->commandes_.insert(std::make_pair(profil->touches_[RECULER], std::make_unique<CommandeRobot>(RECULER, true)));
	profil->commandes_.insert(std::make_pair(profil->touches_[ROTATION_GAUCHE], std::make_unique<CommandeRobot>(ROTATION_GAUCHE, true)));
	profil->commandes_.insert(std::make_pair(profil->touches_[ROTATION_DROITE], std::make_unique<CommandeRobot>(ROTATION_DROITE, true)));

	itr++;

	const rapidjson::Value& comportementsJSON = itr->value;

	if (!comportementsJSON.IsArray())
		return false;

	profil->comportements_.push_back(std::make_unique<ComportementDefaut>(comportementsJSON[DEFAUT]));

	profil->comportements_.push_back(std::make_unique<ComportementSuiviLigne>(comportementsJSON[SUIVIDELIGNE]));

	profil->comportements_.push_back(std::make_unique<ComportementBalayage>(comportementsJSON[BALAYAGE180]));

	profil->comportements_.push_back(std::make_unique<ComportementDeviation>(comportementsJSON[DEVIATIONVERSLAGAUCHE]));

	profil->comportements_.push_back(std::make_unique<ComportementDeviation>(comportementsJSON[DEVIATIONVERSLADROITE]));
	
	profil->comportements_.push_back(std::make_unique<ComportementEvitement>(comportementsJSON[EVITEMENTPARLAGAUCHE]));

	profil->comportements_.push_back(std::make_unique<ComportementEvitement>(comportementsJSON[EVITEMENTPARLADROITE]));

	itr++;

	const rapidjson::Value& capteursDistanceJSON = itr->value;

	if (!capteursDistanceJSON.IsArray())
		return false;

	for (unsigned i = 0; i < capteursDistanceJSON.Size(); i++){
		profil->capteursDistance_.at(i) = CapteurDistance(profil->positionsRelatives_.at(i), profil->anglesRelatifs_.at(i), capteursDistanceJSON[i]);
	}

	itr++;

	profil->suiveurLigne_.assignerActif(itr->value.MemberBegin()->value.GetBool());

	itr++;

	const rapidjson::Value& optionsDebogagesJSON = itr->value;

	if (!optionsDebogagesJSON.IsArray())
		return false;

	for (unsigned optionIndex = 0; optionIndex < optionsDebogagesJSON.Size(); optionIndex++)
	{
		profil->optionsDebogages_[optionIndex] = optionsDebogagesJSON[optionIndex].GetBool();
	}

	return true;
}
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////