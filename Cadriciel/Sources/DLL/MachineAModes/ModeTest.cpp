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
        const bool estRepetition = ((HIWORD(lParam) & KF_REPEAT) == KF_REPEAT);
        if (!estRepetition)
        {
		    controleRobot_->traiterCommande(profil_->obtenirCommandeRobot(wParam), true);
        }
	}
	else if (msg == WM_KEYUP)
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
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////