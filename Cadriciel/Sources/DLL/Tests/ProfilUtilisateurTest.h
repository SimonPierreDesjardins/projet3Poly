////////////////////////////////////////////////
/// @file   ControleRobotTest.h
/// @author Philippe Marcotte
/// @date   2016-03-20
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef TESTS_PROFIL_UTILISATEUR_H
#define TESTS_PROFIL_UTILISATEUR_H

#include <cppunit/extensions/HelperMacros.h>
#include "ProfilUtilisateur.h"

///////////////////////////////////////////////////////////////////////////
/// @class ControleRobotTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement du 
/// chargement d'un profil et de l'assignation des touches.
///
/// @author Philippe Marcotte
/// @date 2016-03-20
///////////////////////////////////////////////////////////////////////////
class ProfilUtilisateurTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(ProfilUtilisateurTest);
	CPPUNIT_TEST(testChargerProfil);

	CPPUNIT_TEST(testAssignerTouche);
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

	void testChargerProfil();
	void testAssignerTouche();

private:
	ProfilUtilisateur* profilCorrect;
	const std::string nomProfilTest = "profilTest.profil";
	bool chargerProfil(ProfilUtilisateur* profil);
};

#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////