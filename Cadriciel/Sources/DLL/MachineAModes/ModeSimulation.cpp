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
/// @fn ModeSimulation::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
/// Fonction qui permet de traiter les entrées utilisateur en mode simulation. 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void ModeSimulation::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		controleRobot_->traiterCommande(profil_->obtenirCommandeRobot(wParam));
	}
	else if (msg == WM_KEYUP)
	{
		CommandeRobot* commande = profil_->obtenirCommandeRobot(wParam);
		if (commande != nullptr && commande->obtenirTypeCommande() != INVERSER_MODE_CONTROLE)
		{
			std::unique_ptr<CommandeRobot> commande = std::make_unique<CommandeRobot>(ARRETER);
			controleRobot_->traiterCommande(commande.get());
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////