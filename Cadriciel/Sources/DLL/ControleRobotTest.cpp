////////////////////////////////////////////////////////////////////////////////////
/// @file ControleRobotTest.cpp
/// @author Camille Gendreau
/// @date 2016-03-18
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ControleRobotTest.h"
#include "ControleRobot.h"
#include "ComportementAbstrait.h"
#include "ComportementDefaut.h"
#include "ComportementBalayage.h"
#include "ComportementSuiviLigne.h"
#include "ComportementDeviation.h"
#include "ComportementEvitement.h"


// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ControleRobotTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleRobotTest::setUp()
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
void ControleRobotTest::setUp()
{


	// On construit le controleur du robot
	controleRobot_ = new ControleRobot();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleRobotTest::tearDown()
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
void ControleRobotTest::tearDown()
{
	delete controleRobot_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleRobotTest::testAssignationVectComportements()
///
/// Test l'assignation du pointeur vers un vecteur de comportements pour le robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobotTest::testAssignationVectComportements(){

	std::vector<std::unique_ptr<ComportementAbstrait>> testVector;

	controleRobot_->assignerVecteurComportements(&testVector);

	CPPUNIT_ASSERT(controleRobot_->vecteurComportements_ == &testVector);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleRobotTest::testAssignationDeComportement()
///
/// Cette fonction test l'assignation de comportements au controleur du Robot
/// Il assure que  lorsqu'on appelle l'assignation d'un comportement, c'est bel et bien ce comportement qui et assigné au robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobotTest::testAssignationDeComportement(){

	// On popule le vecteur de comportements à tester
	/*TypeComportement
	DEFAUT,
	SUIVIDELIGNE,
	BALAYAGE180,
	DEVIATIONVERSLAGAUCHE,
	DEVIATIONVERSLADROITE,
	EVITEMENTPARLAGAUCHE,
	EVITEMENTPARLADROITE*/
	comportements_.push_back(std::make_unique <ComportementDefaut>());
	comportements_.push_back(std::make_unique <ComportementSuiviLigne>());
	comportements_.push_back(std::make_unique <ComportementBalayage>());
	comportements_.push_back(std::make_unique <ComportementDeviation>());
	comportements_.push_back(std::make_unique <ComportementDeviation>());
	comportements_.push_back(std::make_unique <ComportementEvitement>());
	comportements_.push_back(std::make_unique <ComportementEvitement>());

	// On assigne ce vecteur au robot
	controleRobot_->assignerVecteurComportements(&comportements_);

	std::wstring declencheur = L"Test de chagement de comportement";

    
	controleRobot_->assignerComportement(DEFAUT, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find(L"ComportementDefaut") != std::wstring::npos);
	
	controleRobot_->assignerComportement(SUIVIDELIGNE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find(L"ComportementSuiviLigne") != std::wstring::npos);
	
	controleRobot_->assignerComportement(BALAYAGE180, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find(L"ComportementBalayage") != std::wstring::npos);
	
	controleRobot_->assignerComportement(DEVIATIONVERSLAGAUCHE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find(L"ComportementDeviation") != std::wstring::npos);
	
	controleRobot_->assignerComportement(DEVIATIONVERSLADROITE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find(L"ComportementDeviation") != std::wstring::npos);
	
	controleRobot_->assignerComportement(EVITEMENTPARLAGAUCHE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find(L"ComportementEvitement") != std::wstring::npos);
	
	controleRobot_->assignerComportement(EVITEMENTPARLAGAUCHE, declencheur);
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find(L"ComportementEvitement") != std::wstring::npos);
}


void ControleRobotTest::testPassageModeAutomatique(){
	/*
	controleRobot_->passerAModeManuel();
	controleRobot_->assignerComportement(BALAYAGE180, L"Test de passage au mode automatique");
	controleRobot_->passerAModeAutomatique();
	CPPUNIT_ASSERT(controleRobot_->comportement_->obtenirNomComportement().find(L"ComportementDefaut") != std::wstring::npos);
    */
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleRobotTest::testPassageModeManuel()
///
/// Test le passage au mode manuel pour le robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobotTest::testPassageModeManuel(){
	controleRobot_->passerAModeManuel();
	CPPUNIT_ASSERT(controleRobot_->logiqueRobot == nullptr);
	CPPUNIT_ASSERT(controleRobot_->manuel == true);
}

void ControleRobotTest::testAlternanceModeManuelAuto(){
	//controleRobot_->passerAModeAutomatique();
	controleRobot_->inverserModeControle();
	CPPUNIT_ASSERT(controleRobot_->logiqueRobot == nullptr);
	CPPUNIT_ASSERT(controleRobot_->manuel == true);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
