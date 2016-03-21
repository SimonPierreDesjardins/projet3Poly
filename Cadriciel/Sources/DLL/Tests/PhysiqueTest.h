//////////////////////////////////////////////////////////////////////////////
/// @file PhysiqueTest.h
/// @author Olivier St-Amour 
/// @date 2016-02-29
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef PHYSIQUE_TEST_H
#define PHYSIQUE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "Utilitaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe NoeudAbstrait
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class PhysiqueTest : public CppUnit::TestFixture
{

// =================================================================
// Déclaration de la suite de tests et des méthodes de tests
//
// Important, vous devez définir chacun de vos cas de tests à l'aide
// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
// =================================================================
  CPPUNIT_TEST_SUITE( PhysiqueTest );
  CPPUNIT_TEST(testIntersectionQuad);

  CPPUNIT_TEST(testPointDansCercle);
  CPPUNIT_TEST(testPointDansRectangle);

  CPPUNIT_TEST(testIntersectionRectangleRectangle);
  CPPUNIT_TEST(testCalculerIntersectionRectangleRectangle);
  CPPUNIT_TEST(testCalculerIntersectionCercleRectangle);
  CPPUNIT_TEST(testCalculerIntersectionCercleCercle);

  CPPUNIT_TEST(testColisionRectangleRectangle);
  CPPUNIT_TEST(testColisionCercleRectangle);
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

	/// Cas de test: verification de l'intersection de deux quads.
	void testIntersectionQuad();

    void testPointDansRectangle();
    void testPointDansCercle();

	void testIntersectionRectangleRectangle();
	void testCalculerIntersectionRectangleRectangle();
	void testCalculerIntersectionCercleRectangle();
	void testCalculerIntersectionCercleCercle();

	void testColisionRectangleRectangle();
	void testColisionCercleRectangle();

private:
    utilitaire::QuadEnglobant quad1_;
    utilitaire::QuadEnglobant quad2_;
};

#endif // PHYSIQUE_TEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
