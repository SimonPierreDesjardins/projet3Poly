///////////////////////////////////////////////////////////////////////////
/// @file ModeSimulation.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeSimulation.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
#include "NoeudRobot.h"
#include "CommandeRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeSimulation::ModeSimulation()
///
/// Constructeur par défaut pour le mode simulation
///
////////////////////////////////////////////////////////////////////////
ModeSimulation::ModeSimulation()
{
	shared_ptr<NoeudRobot> robot = std::dynamic_pointer_cast<NoeudRobot>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud("NOM_ROBOT"));
	typeMode_ = SIMULATION;
	controleRobot_ = std::make_unique<ControleRobot>();
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
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
}

void ModeSimulation::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		controleRobot_->traiterCommande(profil_->obtenirCommandeRobot(wParam));
	}
	else if (msg == WM_KEYUP)
	{
		std::unique_ptr<CommandeRobot> commande = std::make_unique<CommandeRobot>(ARRETER);
		controleRobot_->traiterCommande(commande.get());
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////