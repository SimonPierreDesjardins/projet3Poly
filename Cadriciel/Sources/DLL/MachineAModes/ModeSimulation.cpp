///////////////////////////////////////////////////////////////////////////
/// @file ModeSimulation.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include <math.h>

#include "ModeSimulation.h"
#include "Utilitaire.h"
#include "Vue.h"
#include "Projection.h"
#include "FacadeModele.h"

#include "NoeudRobot.h"
#include "CommandeRobot.h"

#include <iostream>

std::array<char, 10> ModeSimulation::touchesNonConfigurable_ = { { '+', '-', '\b', '1', '2', '3', 'J', 'K', 'L', 'B' } };

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeSimulation::ModeSimulation()
///
/// Constructeur par défaut pour le mode simulation
///
////////////////////////////////////////////////////////////////////////
ModeSimulation::ModeSimulation()
{
	typeMode_ = SIMULATION;
	controleRobot_ = std::make_unique<ControleRobot>();
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
	// On fait démarrer le robot en mode automatique
	controleRobot_->passerAModeAutomatique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeSimulation::~ModeSimulation()
///
/// Destructeur de la classe ModeSimulation
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ModeSimulation::~ModeSimulation()
{
	controleRobot_ = nullptr;
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
void ModeSimulation::inverserLumiereAmbiante()
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
void ModeSimulation::inverserLumiereDirectionnelle()
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
void ModeSimulation::inverserLumiereSpot()
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
/// @fn ModeSimulation::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
/// Fonction qui permet de traiter les entrées utilisateur en mode simulation. 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void ModeSimulation::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN )
	{
		switch (wParam)
		{
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

		case '3':
			break;

		case 'B':
			break;

		case '\b':
			break;

		case VK_ESCAPE:
			controleRobot_->setEnPause(!(controleRobot_->getEnPause()));
			if (!controleRobot_->getEnPause())
			{
				profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
				controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
				controleRobot_->initialiserBoucleRobot();
			}
			else
				controleRobot_->terminerBoucleRobot();

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