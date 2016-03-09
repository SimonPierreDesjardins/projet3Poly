
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
#include "RectangleEnglobant.h"


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

void PhysiqueTest::testIntersectionRectangleRectangle()
{
    glm::dvec3 position = { 0.0, 0.0, 0.0 };
    RectangleEnglobant rectangle1 = RectangleEnglobant(position, 0.0, 4.0, 3.0);

    position = { 30.0, 30.0, 0.0};
    RectangleEnglobant rectangle2 = RectangleEnglobant(position, 0.0, 4.0, 3.0);
    bool intersection = rectangle1.calculerIntersectionRectangle(rectangle2);
    CPPUNIT_ASSERT(!intersection);
    
    rectangle2.assignerAngle(45.0);
    rectangle2.assignerPositionCentre({5.0, 5.0, 5.0});
    intersection = rectangle1.calculerIntersectionRectangle(rectangle2);
    CPPUNIT_ASSERT(!intersection);

    position = { 0.0, 2.5, 0.0 };
    rectangle2.assignerPositionCentre(position);
    intersection = rectangle1.calculerIntersectionRectangle(rectangle2);
    CPPUNIT_ASSERT(intersection);

    position = { -2.5, 0.0, 0.0 };
    rectangle2.assignerPositionCentre(position);
    intersection = rectangle1.calculerIntersectionRectangle(rectangle2);
    CPPUNIT_ASSERT(intersection);

    position = { 0.0, -2.5, 0.0 };
    rectangle2.assignerPositionCentre(position);
    intersection = rectangle1.calculerIntersectionRectangle(rectangle2);
    CPPUNIT_ASSERT(intersection);

    rectangle1.assignerHauteur(1.0);
    rectangle1.assignerLargeur(10.0);

    rectangle2.assignerHauteur(1.0);
    rectangle2.assignerLargeur(10.0);
    rectangle2.assignerAngle(135.0);
    position = { 0.0, 0.0, 0.0 };
    rectangle2.assignerPositionCentre(position);

    intersection = rectangle1.calculerIntersectionRectangle(rectangle2);
    CPPUNIT_ASSERT(intersection);
}

void PhysiqueTest::testIntersectionRectangleCercle()
{
    CPPUNIT_ASSERT(true);
}

void PhysiqueTest::testIntersectionCercleCercle()
{
    CPPUNIT_ASSERT(true);
}


void PhysiqueTest::testPointDansRectangle()
{
    glm::dvec3 positionRectangle = { 20.0, 20.0, 0.0 };
    RectangleEnglobant rectangle(positionRectangle, 0.0, 2.0, 10.0);
    glm::dvec3 point{ 0.0, 0.0, 0.0 };
    double angle = 0.0;
    bool pointDansForme = false;
    for (int i = 0; i < 361; i++)
    {
        rectangle.assignerAngle((double)(i));
        point = { 19.5, 19.5, 0.0 };
        pointDansForme = rectangle.calculerPointEstDansForme(point);
        CPPUNIT_ASSERT(pointDansForme);

        point = { 20.5, 19.5, 0.0 };
        pointDansForme = rectangle.calculerPointEstDansForme(point);
        CPPUNIT_ASSERT(pointDansForme);

        point = { 19.5, 20.5, 0.0 };
        pointDansForme = rectangle.calculerPointEstDansForme(point);
        CPPUNIT_ASSERT(pointDansForme);

        point = { 20.5, 20.5, 0.0 };
        pointDansForme = rectangle.calculerPointEstDansForme(point);
        CPPUNIT_ASSERT(pointDansForme);
        
        point = { 0.0, 0.0, 0.0 };
        pointDansForme = rectangle.calculerPointEstDansForme(point);
        CPPUNIT_ASSERT(!pointDansForme);
    }

}

void PhysiqueTest::testPointDansCercle()
{
    CPPUNIT_ASSERT(true);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////