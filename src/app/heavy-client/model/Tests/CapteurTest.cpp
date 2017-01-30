////////////////////////////////////////////////////////////////////////////////////
/// @file CapteurTest.cpp
/// @author Fr�d�ric Gr�goire
/// @date 2016-03-21
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudLigne.h"
#include "NoeudSegment.h"
#include "NoeudAbstraitTest.h"
#include "CapteurTest.h"
#include "Utilitaire.h"
#include "CapteurDistance.h"
#include "CapteurOptique.h"
#include "SuiveurLigne.h"
#include "ArbreRendu.h"
#include "ArbreRenduINF2990.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(CapteurTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurTest::setUp()
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
void CapteurTest::setUp()
{
	noeud = std::make_unique<NoeudLigne>(ArbreRenduINF2990::NOM_LIGNENOIRE);
	segment = std::make_shared<NoeudSegment>(ArbreRenduINF2990::NOM_SEGMENT);
	noeud->ajouter(segment);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurTest::tearDown()
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
void CapteurTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurTest::TestSuiverLigne()
///
///	Permet de v�rifier l'�tat de chaque capteur et toutes les m�thodes n�cessaires
/// pour valider cette information
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CapteurTest::testSuiverLigne()
{
	SuiveurLigne suiveurLigne;
	glm::dvec3 position{ 0, 0, 0 };

	segment->obtenirFormeEnglobante()->assignerHauteur(4);
	segment->obtenirFormeEnglobante()->assignerLargeur(40);

	suiveurLigne.mettreAJourCapteurs(position, 0);
	suiveurLigne.verifierDetection(noeud.get());
	
	CPPUNIT_ASSERT(7 == suiveurLigne.obtenirEtatCapteurs());

	segment->obtenirFormeEnglobante()->assignerHauteur(0.2);
	segment->obtenirFormeEnglobante()->assignerLargeur(40);

	suiveurLigne.mettreAJourCapteurs(position, 0);
	suiveurLigne.verifierDetection(noeud.get());

	CPPUNIT_ASSERT(2 == suiveurLigne.obtenirEtatCapteurs());

	segment->obtenirFormeEnglobante()->assignerHauteur(0);
	segment->obtenirFormeEnglobante()->assignerLargeur(0);

	suiveurLigne.mettreAJourCapteurs(position, 0);
	suiveurLigne.verifierDetection(noeud.get());

	CPPUNIT_ASSERT(0 == suiveurLigne.obtenirEtatCapteurs());

	position = { 4.7, 1, 0 };
	segment->obtenirFormeEnglobante()->assignerHauteur(0.2);
	segment->obtenirFormeEnglobante()->assignerLargeur(0.2);
	segment->obtenirFormeEnglobante()->assignerPositionCentre(position);
	position = { 0, 0, 0 };
	
	suiveurLigne.mettreAJourCapteurs(position, 0);
	suiveurLigne.verifierDetection(noeud.get());

	CPPUNIT_ASSERT(4 == suiveurLigne.obtenirEtatCapteurs());

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
