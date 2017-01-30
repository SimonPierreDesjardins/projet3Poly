
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
#include "CercleEnglobant.h"


// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(PhysiqueTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
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
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
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
/// Cas de test: �criture/lecture de la position relative
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

	// Premier test : on v�rifie 2 quads qui ne sont pas en intersection.
    quad2_.coins[0] = { 0.0, 3.0, 0.0 };
    quad2_.coins[1] = { 3.0, 6.0, 0.0 };
    quad2_.coins[2] = { 6.0, 3.0, 0.0 };
    quad2_.coins[3] = { 3.0, 0.0, 0.0 };

    intersection = utilitaire::calculerIntersectionDeuxQuads(quad1_, quad2_) &&
                   utilitaire::calculerIntersectionDeuxQuads(quad2_, quad1_);
    CPPUNIT_ASSERT(!intersection);
 
    // Deuxieme test : on v�rifie 1 quad ayant un coin dans un autre quad. 
    quad2_.coins[0] = { 0.0, 0.0, 0.0 };

    intersection = utilitaire::calculerIntersectionDeuxQuads(quad1_, quad2_) &&
                   utilitaire::calculerIntersectionDeuxQuads(quad2_, quad1_);
    CPPUNIT_ASSERT(intersection);
    
    // Troisi�me test : on v�rifie un quad dans un autre quad. 
    quad2_.coins[0] = { 1.0, 0.0, 0.0 };
    quad2_.coins[1] = {-1.0, 0.0, 0.0 };
    quad2_.coins[2] = { 0.0,-1.0, 0.0 };
    quad2_.coins[3] = { 0.0, 1.0, 0.0 };

    intersection = utilitaire::calculerIntersectionDeuxQuads(quad1_, quad2_) &&
                   utilitaire::calculerIntersectionDeuxQuads(quad2_, quad1_);
    CPPUNIT_ASSERT(intersection);

    // Quatri�me test : on v�rifie l'intersection de deux quads identiques.
    quad2_ = quad1_;
    intersection = utilitaire::calculerIntersectionDeuxQuads(quad1_, quad2_) &&
                   utilitaire::calculerIntersectionDeuxQuads(quad2_, quad1_);
    CPPUNIT_ASSERT(intersection);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::testIntersectionRectangleRectangle()
///
/// Cas de test: permet de savoir s'il y a une collision avec un rectangle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testIntersectionRectangleRectangle()
{
    glm::dvec3 position = { 0.0, 0.0, 0.0 };
    RectangleEnglobant rectangle1 = RectangleEnglobant(position, 0.0 ,4.0, 3.0);

    // Test sur un cas de rectangle �loign� avec un angle identique.
    position = { 30.0, 30.0, 0.0};
    RectangleEnglobant rectangle2 = RectangleEnglobant(position, 0.0, 4.0, 3.0);
    bool intersection = rectangle1.calculerIntersection(rectangle2);
    CPPUNIT_ASSERT(!intersection);
    
    rectangle2.assignerAngle(45.0);
    rectangle2.assignerPositionCentre({5.0, 5.0, 5.0});
    intersection = rectangle1.calculerIntersection(rectangle2);
    CPPUNIT_ASSERT(!intersection);

    position = { 0.0, 2.5, 0.0 };
    rectangle2.assignerPositionCentre(position);
    intersection = rectangle1.calculerIntersection(rectangle2);
    CPPUNIT_ASSERT(intersection);

    position = { -2.5, 0.0, 0.0 };
    rectangle2.assignerPositionCentre(position);
    intersection = rectangle1.calculerIntersection(rectangle2);
    CPPUNIT_ASSERT(intersection);

    position = { 0.0, -2.5, 0.0 };
    rectangle2.assignerPositionCentre(position);
    intersection = rectangle1.calculerIntersection(rectangle2);
    CPPUNIT_ASSERT(intersection);

    rectangle1.assignerHauteur(1.0);
    rectangle1.assignerLargeur(10.0);

    rectangle2.assignerHauteur(1.0);
    rectangle2.assignerLargeur(10.0);
    rectangle2.assignerAngle(135.0);
    position = { 0.0, 0.0, 0.0 };
    rectangle2.assignerPositionCentre(position);

    intersection = rectangle1.calculerIntersection(rectangle2);
    CPPUNIT_ASSERT(intersection);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::testPointDansRectangle()
///
/// Cas de test: permet de savoir si un point est a l'int�rieur ou non de la
/// bo�te englobante du rectangle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testPointDansRectangle()
{
    glm::dvec3 positionRectangle = { 0.0, 0.0, 0.0 };
    RectangleEnglobant rectangle(positionRectangle, 0.0, 48.0, 96.0);

	//V�rifier les quatre coins limite de la boite et le centre
    glm::dvec3 point{ 0.0, 0.0, 0.0 };
    bool pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);

    point = { 48, 24, 0.0 };
    pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);

    point = { 48, -24, 0.0 };
    pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);

    point = { -48, -24, 0.0 };
    pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);

    point = { -48, 24, 0.0 };
    pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);

    //Quelques points al�atoires
	point = { 15, 15, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { -38, -19, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { -100, 30, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	//V�rifier les quatres centre extreme de la boite
    point = { 0.0, 24, 0.0 };
    pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);

    point = { 48, 0.0, 0.0 };
    pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);
    
    point = { 0.0, -24, 0.0 };
    pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);

    point = { -48, 0.0, 0.0 };
    pointEstDansForme = rectangle.calculerEstDansForme(point);
    CPPUNIT_ASSERT(pointEstDansForme);

	//V�rifier que le point n'est pas dans la boite au centre extreme
	point = { -48.1, 0.0, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { 48.1, 0.0, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { 0.0, -24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { 0.0, 24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	//V�rifier que le point n'est pas dans la boite au coin sup�rieur gauche
	point = { 48, 24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { 48.1, 24, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { 48.1, 24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	//V�rifier que le point n'est pas dans la boite au coin inf�rieur gauche
	point = { 48, -24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { 48.1, -24, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { 48.1, -24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	//V�rifier que le point n'est pas dans la boite au coin inf�rieur droit
	point = { -48, -24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { -48.1, -24, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { -48.1, -24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	//V�rifier que le point n'est pas dans la boite au coin sup�rieur droit
	point = { -48, 24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { -48.1, 24, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { -48.1, 24.1, 0.0 };
	pointEstDansForme = rectangle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::testPointDansCercle()
///
/// Cas de test: permet de savoir si un point est a l'int�rieur ou non de la
/// bo�te englobante du cercle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testPointDansCercle()
{
	glm::dvec3 positionCercle = { 0.0, 0.0, 0.0 };
	CercleEnglobant cercle(positionCercle, 45);

	//V�rifier les quatre bornes limites du cercle (croix + )
	glm::dvec3 point{ 45, 0.0, 0.0 };
	bool pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { 45, 0.0, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { 0.0, 45.0, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { 0.0, -45.0, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	//V�rifier les quatre bornes limites du cercle (diagonale x )
	point = { 31.819, 31.819, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { 31.819, -31.819, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { -31.819, -31.819, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { -31.819, 31.819, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	//Quelque points al�atoires
	point = { -29, 34, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);

	point = { -45.1, 0, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(!pointEstDansForme);

	point = { 3, -9, 0.0 };
	pointEstDansForme = cercle.calculerEstDansForme(point);
	CPPUNIT_ASSERT(pointEstDansForme);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::testCalculerIntersectionRectangle()
///
/// Cas de test: permet de savoir si un rectangle est a l'int�rieur ou non de la
/// bo�te englobante d'un autre rectangle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testCalculerIntersectionRectangleRectangle()
{
	glm::dvec3 positionRectangleUn = { 0.0, 0.0, 0.0 };
	RectangleEnglobant rectangleUn(positionRectangleUn, 0.0, 20.0, 20.0);

	glm::dvec3 positionRectangleDeux = { -40.0, 40.0, 0.0 };
	RectangleEnglobant rectangleDeux(positionRectangleDeux, 0.0, 20.0, 20.0);

	//Condition initiale ne se touche pas
	bool RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(RectangleNeSeTouchePas);

	//Coin de l'un avec coin de l'autre
	positionRectangleDeux = { -20, 20, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	positionRectangleDeux = { 20, 20, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	positionRectangleDeux = { -20, -20, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	positionRectangleDeux = { 20, -20, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	//Coter un par dessous l'autre
	positionRectangleDeux = { -20, 0, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	positionRectangleDeux = { 20, 0, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	positionRectangleDeux = { 0, -20, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	positionRectangleDeux = { 0, -20, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	//Si le rectangleDeux est en angle
	rectangleDeux.assignerAngle(45);

	positionRectangleDeux = { 0, 24.15, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(RectangleNeSeTouchePas);

	positionRectangleDeux = { 0, 24.14, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	positionRectangleDeux = { 10, 24.14, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(!RectangleNeSeTouchePas);

	positionRectangleDeux = { 10, 24.15, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	RectangleNeSeTouchePas = !rectangleUn.calculerIntersection(rectangleDeux);
	CPPUNIT_ASSERT(RectangleNeSeTouchePas);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::testCalculerIntersectionCercleRectangle()
///
/// Cas de test: permet de savoir si un cercle est a l'int�rieur ou non de la
/// bo�te englobante d'un rectangle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testCalculerIntersectionCercleRectangle()
{
	glm::dvec3 positionRectangle = { 0.0, 0.0, 0.0 };
	RectangleEnglobant rectangle(positionRectangle, 0.0, 20.0, 20.0);

	glm::dvec3 positionCercle = { -40.0, 40.0, 0.0 };
	CercleEnglobant cercle(positionCercle, 10); 

	//Condition initiale
	bool RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(RectangleNeTouchePasCercle);

	//V�rifier les quatres mileux du rectangle avec un cercle
	positionCercle = { -20, 0, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(!RectangleNeTouchePasCercle);

	positionCercle = { 20, 0, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(!RectangleNeTouchePasCercle);

	positionCercle = { 0, 20, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(!RectangleNeTouchePasCercle);

	positionCercle = { 0, -20, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(!RectangleNeTouchePasCercle);

	//V�rifier les quatres coins du rectangle avec un cercle
	positionCercle = { -17.07, 17.07, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(!RectangleNeTouchePasCercle);

	positionCercle = { 17.07, 17.07, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(!RectangleNeTouchePasCercle);

	positionCercle = { -17.07, -17.07, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(!RectangleNeTouchePasCercle);

	positionCercle = { 17.07, -17.07, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(!RectangleNeTouchePasCercle);

	//Etre certain que le cercle ne touche pas le rectangle
	positionCercle = { -17.08, 17.08, 0 };
	cercle.assignerPositionCentre(positionCercle);
	RectangleNeTouchePasCercle = !rectangle.calculerIntersection(cercle);
	CPPUNIT_ASSERT(RectangleNeTouchePasCercle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::testCalculerIntersectionCercleCercle()
///
/// Cas de test: permet de savoir si un cercle est a l'int�rieur ou non de la
/// bo�te englobante d'un cercle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testCalculerIntersectionCercleCercle()
{
	glm::dvec3 positionCercleUn = { 0.0, 0.0, 0.0 };
	CercleEnglobant cercleUn(positionCercleUn, 10);

	glm::dvec3 positionCercleDeux = { -40.0, 40.0, 0.0 };
	CercleEnglobant cercleDeux(positionCercleDeux, 10);

	//Condition initiale
	bool CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(CercleNeTouchePasCercle);

	//Les quatre extrimit�s ( + )
	positionCercleDeux = { 0.0, 20.0, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(!CercleNeTouchePasCercle);

	positionCercleDeux = { 0.0, -20.0, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(!CercleNeTouchePasCercle);

	positionCercleDeux = { 20.0, 0.0, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(!CercleNeTouchePasCercle);

	positionCercleDeux = { -20.0, 0.0, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(!CercleNeTouchePasCercle);

	//les quatre coins ( x )
	positionCercleDeux = { 14.14, 14.14, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(!CercleNeTouchePasCercle);

	positionCercleDeux = { -14.14, 14.14, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(!CercleNeTouchePasCercle);

	positionCercleDeux = { 14.14, -14.14, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(!CercleNeTouchePasCercle);

	positionCercleDeux = { -14.14, -14.14, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(!CercleNeTouchePasCercle);

	//Etre certains que les cercles ne se touchent pas
	positionCercleDeux = { 0.0, 20.5, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(CercleNeTouchePasCercle);

	positionCercleDeux = { 14.15, 14.14, 0.0 };
	cercleDeux.assignerPositionCentre(positionCercleDeux);
	CercleNeTouchePasCercle = !cercleUn.calculerIntersection(cercleDeux);
	CPPUNIT_ASSERT(CercleNeTouchePasCercle);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void testColisionRectangle()
///
/// Cas de test: permet de savoir la normale lorsqu'un rectangle est en collision
/// avec un rectangle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testColisionRectangleRectangle()
{
	glm::dvec3 positionRectangleUn = { 0.0, 0.0, 0.0 };
	RectangleEnglobant rectangleUn(positionRectangleUn, 0.0, 20.0, 20.0);

	glm::dvec3 positionRectangleDeux = { 0.0, 40.0, 0.0 };
	RectangleEnglobant rectangleDeux(positionRectangleDeux, 0.0, 20.0, 20.0);

	glm::dvec3 normale = { 0, 0, 0 };

	//Coin de l'un avec coin de l'autre
	positionRectangleDeux = { 0, 20, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	normale = rectangleUn.calculerNormaleCollision(rectangleDeux);
	glm::dvec3 expected = { 0, 1.0, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	positionRectangleDeux = { 0, -20, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	normale = rectangleUn.calculerNormaleCollision(rectangleDeux);
	expected = { 0, -1, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	positionRectangleDeux = { -20, 0, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	normale = rectangleUn.calculerNormaleCollision(rectangleDeux);
	expected = { -1, 0, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	positionRectangleDeux = { 20, 0, 0 };
	rectangleDeux.assignerPositionCentre(positionRectangleDeux);
	normale = rectangleUn.calculerNormaleCollision(rectangleDeux);
	expected = { 1, 0, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void testColisionCercle()
///
/// Cas de test: permet de savoir la normale lorsqu'un rectangle est en collision
/// avec un cercle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testColisionCercleRectangle()
{
	glm::dvec3 positionRectangle = { 0.0, 0.0, 0.0 };
	RectangleEnglobant rectangle(positionRectangle, 0.0, 20.0, 20.0);

	glm::dvec3 positionCercle = { 40.0, 0.0, 0.0 };
	CercleEnglobant cercle(positionCercle, 10);

	glm::dvec3 normale = { 0, 0, 0 };

	//V�rifier les quatre face du robot ( + )
	positionCercle = { 20, 0, 0 };
	cercle.assignerPositionCentre(positionCercle);
	normale = rectangle.calculerNormaleCollision(cercle);
	glm::dvec3 expected = { 1, 0, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	positionCercle = { -20, 0, 0 };
	cercle.assignerPositionCentre(positionCercle);
	normale = rectangle.calculerNormaleCollision(cercle);
	expected = { -1, 0, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	positionCercle = { 0, 20, 0 };
	cercle.assignerPositionCentre(positionCercle);
	normale = rectangle.calculerNormaleCollision(cercle);
	expected = { 0, 1, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	positionCercle = { 0, -20, 0 };
	cercle.assignerPositionCentre(positionCercle);
	normale = rectangle.calculerNormaleCollision(cercle);
	expected = { 0, -1, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PhysiqueTest::testColisionRectanglePoint()
///
/// Cas de test: permet de savoir la normale lorsqu'un rectangle est en collision
/// avec un point
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PhysiqueTest::testColisionRectanglePoint()
{
	glm::dvec3 positionRectangle = { 0.0, 0.0, 0.0 };
	RectangleEnglobant rectangle(positionRectangle, 0.0, 20.0, 20.0);

	glm::dvec3 point{ 0.0, 0.0, 0.0 };

	glm::dvec3 normale = { 0, 0, 0 };

	//V�rifier les quatre face du robot ( + )
	point = { 10, 0, 0 };
	normale = rectangle.calculerNormaleCollision(point);
	glm::dvec3 expected = { 1, 0, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	point = { -10, 0, 0 };
	normale = rectangle.calculerNormaleCollision(point);
	expected = { -1, 0, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	point = { 0, 10, 0 };
	normale = rectangle.calculerNormaleCollision(point);
	expected = { 0, 1, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);

	point = { 0, -10, 0 };
	normale = rectangle.calculerNormaleCollision(point);
	expected = { 0, -1, 0 };
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[0], normale[0], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[1], normale[1], 0.1);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[2], normale[2], 0.1);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
