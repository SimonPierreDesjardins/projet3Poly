//////////////////////////////////////////////////////////////////////////////
/// @file CapteurTest.h
/// @author Frédéric Grégoire
/// @date 2016-03-21
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef CAPTEUR_TEST_H
#define CAPTEUR_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "Utilitaire.h"
#include "ArbreRendu.h"
#include "ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class CapteurTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe Capteur
///
/// @author Frédéric Grégoire
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class CapteurTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(CapteurTest);
	
	CPPUNIT_TEST(testSuiverLigne);

	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================
	void testSuiverLigne();

private:
	/// Instance d'un noeud abstrait
	std::shared_ptr<NoeudLigne> noeud;
	std::shared_ptr<NoeudSegment> segment;

};

#endif // CAPTEUR_TEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
