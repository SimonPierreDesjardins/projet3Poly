//////////////////////////////////////////////////////////////////////////////
/// @file CapteurTest.h
/// @author Fr�d�ric Gr�goire
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
///        m�thodes de la classe Capteur
///
/// @author Fr�d�ric Gr�goire
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class CapteurTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(CapteurTest);
	
	CPPUNIT_TEST(testSuiverLigne);

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
