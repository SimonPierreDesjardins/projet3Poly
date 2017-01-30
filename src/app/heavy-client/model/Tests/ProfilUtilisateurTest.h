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
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(ProfilUtilisateurTest);
	CPPUNIT_TEST(testChargerProfil);

	CPPUNIT_TEST(testAssignerTouche);
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

	void testChargerProfil();
	void testAssignerTouche();

private:
	/// Pointeur vers le profil ayant les attributs correctement charg�s
	ProfilUtilisateur* profilCorrect;

	/// Pointeur vers le profil dans lequel on test la fonction charger
	ProfilUtilisateur* profilTest;

	/// Nom du fichier test
	const std::string nomProfilTest = "profilTest.profil";

	/// Fonction adapt�e pour les tests du ProfilUtilisateur
	bool chargerProfil(ProfilUtilisateur* profil);
};

#endif
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////