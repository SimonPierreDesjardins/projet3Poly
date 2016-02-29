
////////////////////////////////////////////////////////////////////////////////////
/// @file PhysiqueTest.cpp
/// @author Olivier St-Amour
/// @date 2016-02-29
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "PhysiqueTest.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(PhysiqueTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::setUp()
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
void PhysiqueTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::tearDown()
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
void PhysiqueTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::testIntersectionQuad()
///
/// Cas de test: écriture/lecture de la position relative
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testIntersectionQuad()
{ 
    bool intersection = false;
    
    quad1_.coins[0] = {-2.0, 0.0, 0.0 };
    quad1_.coins[1] = { 0.0, 2.0, 0.0 };
    quad1_.coins[2] = { 2.0, 0.0, 0.0 };
    quad1_.coins[3] = { 0.0,-2.0, 0.0 };

	// Premier test : on vérifie 2 quads qui ne sont pas en intersection.
    quad2_.coins[0] = { 0.0, 3.0, 0.0 };
    quad2_.coins[1] = { 3.0, 6.0, 0.0 };
    quad2_.coins[2] = { 6.0, 3.0, 0.0 };
    quad2_.coins[3] = { 3.0, 0.0, 0.0 };

    intersection = utilitaire::calculerIntersectionDeuxQuads(quad1_, quad2_) &&
                   utilitaire::calculerIntersectionDeuxQuads(quad2_, quad1_);
    CPPUNIT_ASSERT(!intersection);
 
    // Deuxieme test : on vérifie 1 quad ayant un coin dans un autre quad. 
    quad2_.coins[0] = { 0.0, 0.0, 0.0 };

    intersection = utilitaire::calculerIntersectionDeuxQuads(quad1_, quad2_) &&
                   utilitaire::calculerIntersectionDeuxQuads(quad2_, quad1_);
    CPPUNIT_ASSERT(intersection);
    
    // Troisième test : on vérifie un quad dans un autre quad. 
    quad2_.coins[0] = { 1.0, 0.0, 0.0 };
    quad2_.coins[1] = {-1.0, 0.0, 0.0 };
    quad2_.coins[2] = { 0.0,-1.0, 0.0 };
    quad2_.coins[3] = { 0.0, 1.0, 0.0 };

    intersection = utilitaire::calculerIntersectionDeuxQuads(quad1_, quad2_) &&
                   utilitaire::calculerIntersectionDeuxQuads(quad2_, quad1_);
    CPPUNIT_ASSERT(intersection);

    // Quatrième test : on vérifie l'intersection de deux quads identiques.
    quad2_ = quad1_;
    intersection = utilitaire::calculerIntersectionDeuxQuads(quad1_, quad2_) &&
                   utilitaire::calculerIntersectionDeuxQuads(quad2_, quad1_);
    CPPUNIT_ASSERT(intersection);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
