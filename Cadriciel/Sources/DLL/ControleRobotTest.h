#ifndef TESTS_COMPORTEMENTS_H
#define TESTS_COMPORTEMENTS_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "ControleRobot.h"
#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class ControleRobotTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement du changement de comportements
/// dans le controleur de Robot.
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class ControleRobotTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(ControleRobotTest);
	CPPUNIT_TEST(testAssignationDeComportement);

	CPPUNIT_TEST(testComportementPassageModeAutomatique);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test: assignationDeComportements
	void testAssignationVectComportements();
	void testAssignationDeComportement();
	void testComportementPassageModeAutomatique();

private:
	ControleRobot* controleRobot_;
	std::vector < std::unique_ptr<ComportementAbstrait> > comportements_;

};

#endif