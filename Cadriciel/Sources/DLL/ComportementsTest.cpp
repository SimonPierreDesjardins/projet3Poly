////////////////////////////////////////////////////////////////////////////////////
/// @file PhysiqueTest.cpp
/// @author Olivier St-Amour
/// @date 2016-02-29
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ComportementsTest.h"
#include "ControleRobot.h"
#include "ComportementAbstrait.h"
#include "ComportementDefaut.h"
#include "ComportementBalayage.h"
#include "ComportementSuiviLigne.h"
#include "ComportementDeviation.h"
#include "ComportementEvitement.h"


// Enregistrement de la suite de tests au sein du registre
//CPPUNIT_TEST_SUITE_REGISTRATION(ComportementsTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ComportementsTest::setUp()
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
void ComportementsTest::setUp()
{
	/*TypeComportement
		DEFAUT,
		SUIVIDELIGNE,
		BALAYAGE180,
		DEVIATIONVERSLAGAUCHE,
		DEVIATIONVERSLADROITE,
		EVITEMENTPARLAGAUCHE,
		EVITEMENTPARLADROITE*/
	//On construit le vecteur des comportements
	comportements_.push_back(std::make_unique <ComportementDefaut>());
	comportements_.push_back(std::make_unique <ComportementSuiviLigne>());
	comportements_.push_back(std::make_unique <ComportementBalayage>());
	comportements_.push_back(std::make_unique <ComportementDeviation>());
	comportements_.push_back(std::make_unique <ComportementDeviation>());
	comportements_.push_back(std::make_unique <ComportementEvitement>());
	comportements_.push_back(std::make_unique <ComportementEvitement>());

	// On construit le controleur du robot
	controleRobot_ = new ControleRobot();
	controleRobot_ -> assignerVecteurComportements(&comportements_);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ComportementsTest::tearDown()
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
void ComportementsTest::tearDown()
{
	delete controleRobot_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ComportementsTest::testAssignationDeComportement()
///
/// Cette fonction test l'assignation de comportements au controleur du Robot
/// Il assure que  lorsqu'on appelle l'assignation d'un comportement, c'est bel et bien ce comportement qui et assigné au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementsTest::testAssignationDeComportement(){
	/*TypeComportement
	DEFAUT,
	SUIVIDELIGNE,
	BALAYAGE180,
	DEVIATIONVERSLAGAUCHE,
	DEVIATIONVERSLADROITE,
	EVITEMENTPARLAGAUCHE,
	EVITEMENTPARLADROITE*/
	std::string declencheur = "Test de chagement de comportement";

	controleRobot_->assignerComportement(DEFAUT, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find("ComportementDefaut") != std::string::npos);

	controleRobot_->assignerComportement(SUIVIDELIGNE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find("ComportementSuiviLigne") != std::string::npos);

	controleRobot_->assignerComportement(BALAYAGE180, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find("ComportementBalayage") != std::string::npos);

	controleRobot_->assignerComportement(DEVIATIONVERSLAGAUCHE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find("ComportementDeviation") != std::string::npos);

	controleRobot_->assignerComportement(DEVIATIONVERSLADROITE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find("ComportementDeviation") != std::string::npos);
	
	controleRobot_->assignerComportement(EVITEMENTPARLAGAUCHE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find("ComportementEvitement") != std::string::npos);

	controleRobot_->assignerComportement(EVITEMENTPARLAGAUCHE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find("ComportementEvitement") != std::string::npos);

}


void ComportementsTest::testComportementPassageModeAutomatique(){
	controleRobot_->passerAModeManuel();
	controleRobot_->assignerComportement(BALAYAGE180, "Test de passage au mode automatique");
	controleRobot_->passerAModeAutomatique();
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find("ComportementDefaut") != std::string::npos);
}