///////////////////////////////////////////////////////////////////////////
/// @file ModeTest.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include <math.h>
#include "ModeTest.h"
#include "Utilitaire.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

#include <iostream>

std::array<char, 9> ModeTest::touchesNonConfigurable_ = { { '+', '-', '\b', '1', '2', 'J', 'K', 'L', 'B' } };

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTest::ModeTest()
///
/// Constructeur par défaut pour le mode test
///
////////////////////////////////////////////////////////////////////////
ModeTest::ModeTest()
{
	typeMode_ = TEST;
	controleRobot_ = std::make_unique<ControleRobot>();
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
	// On fait démarrer le robot en mode automatique
	controleRobot_->passerAModeAutomatique();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTest::~ModeTest()
///
/// Destructeur de la classe ModeTest
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ModeTest::~ModeTest()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTest::preChangementDeProfil()
///
/// Fonction appelée avant qu'il y ait changement de profil pour arrêter les accès. Arrête aussi le thread du robot.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::preChangementDeProfil(){
	//Terminer le thread du robot et préparer à un changement au mode automatique
	controleRobot_->passerAModeManuel();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTest::postChangementDeProfil()
///
/// Fonction appelée après qu'il y ait changement de profil pour repartir la simulation. Passe le robot en mode automatique.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::postChangementDeProfil(){
	//Repartir le thread en mode automatique, comportement defaut
	controleRobot_->passerAModeAutomatique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererTouchePlus()
///
/// Cette fonction permet de gérer la touche + dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom in.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererTouchePlus()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	}
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheMoins()
///
/// Cette fonction permet de gérer la touche - dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom out.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererToucheMoins()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	}
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheGauche()
///
/// Cette fonction permet de gérer la touche flèche gauche dans le modeEdition.
///
/// Fait un déplacement de 10 pixels selon l'axe des x.
///
////////////////////////////////////////////////////////////////////////

void ModeTest::gererFlecheGauche()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(10, 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheBas()
///
/// Cette fonction permet de gérer la touche flèche bas dans le modeEdition.
///
/// Fait un déplacement de 10 pixels selon l'axe des y.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererFlecheBas()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, 10);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheHaut()
///
/// Cette fonction permet de gérer la touche flèche haut dans le modeEdition.
///
/// Fait un déplacement de -10 pixels selon l'axe des y.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererFlecheHaut()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, -10);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheDroit()
///
/// Cette fonction permet de gérer la touche flèche droit dans le modeEdition.
///
/// Fait un déplacement de -10 pixels selon l'axe des x.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererFlecheDroit()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(-10, 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeSimulation::inverserLumiereAmbiante()
///
/// Fonction qui permet d'alterner l'état de la lumière ambiante 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::inverserLumiereAmbiante()
{
	lumiereAmbiante = !lumiereAmbiante;
	if (profil_->obtenirOptionDebogage(DEBOGAGE_ECLAIRAGE))
	{
		utilitaire::time_in_HH_MM_SS_MMM();
		if (lumiereAmbiante)
			std::cout << " - Lumiere ambiante ouverte" << std::endl;
		else
			std::cout << " - Lumiere ambiante fermee" << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeSimulation::inverserLumiereDirectionnelle()
///
/// Fonction qui permet d'alterner l'état de la lumière directionnelle 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::inverserLumiereDirectionnelle()
{
	lumiereDirectionnelle = !lumiereDirectionnelle;
	if (profil_->obtenirOptionDebogage(DEBOGAGE_ECLAIRAGE))
	{
		utilitaire::time_in_HH_MM_SS_MMM();
		if (lumiereDirectionnelle)
			std::cout << " - Lumiere directionnelle ouverte" << std::endl;
		else
			std::cout << " - Lumiere directionnelle fermee" << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeSimulation::inverserLumiereSpot()
///
/// Fonction qui permet d'alterner l'état de la lumière spot
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::inverserLumiereSpot()
{
	lumiereSpot = !lumiereSpot;
	if (profil_->obtenirOptionDebogage(DEBOGAGE_ECLAIRAGE))
	{
		utilitaire::time_in_HH_MM_SS_MMM();
		if (lumiereSpot)
			std::cout << " - Lumiere spot ouverte" << std::endl;
		else
			std::cout << " - Lumiere spot fermee" << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTest::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
/// Fonction qui permet de traiter les entrées utilisateur en mode test. 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_LEFT:
			gererFlecheGauche();
			break;

		case VK_RIGHT:
			gererFlecheDroit();
			break;

		case VK_UP:
			gererFlecheHaut();
			break;

		case VK_DOWN:
			gererFlecheBas();
			break;

		case VK_OEM_PLUS:
			gererTouchePlus();
			break;

		case VK_OEM_MINUS:
			gererToucheMoins();
			break;

		case 'J':
			inverserLumiereAmbiante();
			break;

		case 'K':
			inverserLumiereDirectionnelle();
			break;

		case 'L':
			inverserLumiereSpot();
			break;

		case '1':
			break;

		case '2':
			break;

		case 'B':
			break;

		case '\b':
			controleRobot_->terminerBoucleRobot();
			controleRobot_->robot_->positionDepart();
			controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
			controleRobot_->passerAModeAutomatique();
			break;

		case VK_ESCAPE:
			controleRobot_->setEnPause(!(controleRobot_->getEnPause()));
			break;

		default:
			break;
		}

		if (!controleRobot_->getEnPause())
		{
			const bool estRepetition = ((HIWORD(lParam) & KF_REPEAT) == KF_REPEAT);
			if (!estRepetition)
			{
				controleRobot_->traiterCommande(profil_->obtenirCommandeRobot(wParam), true);
			}
		}
	}
	else if (msg == WM_KEYUP)
	{
		if (!controleRobot_->getEnPause())
		{
			CommandeRobot* commande = profil_->obtenirCommandeRobot(wParam);
			if (commande != nullptr && commande->obtenirTypeCommande() != INVERSER_MODE_CONTROLE)
			{
				// Obtenir la commande associée et inverser la vitesse des moteurs.
				CommandeRobot* commande = profil_->obtenirCommandeRobot(wParam);
				commande->inverserVitesseMoteurs();
				controleRobot_->traiterCommande(commande, true);

				// Rétablir l'état initial de la commande.
				commande->inverserVitesseMoteurs();
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////