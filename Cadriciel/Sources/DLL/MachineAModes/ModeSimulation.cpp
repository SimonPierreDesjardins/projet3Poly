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
#include "AffichageTexte.h"
#include "ControleurLumiere.h"


#include <iostream>

#include "EnginSon.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

std::array<char, 11> ModeSimulation::touchesNonConfigurable_ = { { '+', '-', '\b', '1', '2', '3', 'J', 'K', 'L', 'B', 'T' } };
  
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
    actionsAppuyees_ = { { false, false, false, false, false } };
	EnginSon::obtenirInstance()->jouerMusique();

    affichageTexte_ = FacadeModele::obtenirInstance()->obtenirAffichageTexte();
    affichageTexte_->assignerProfilEstAffiche(true);
    affichageTexte_->assignerTempsEstAffiche(true);
    affichageTexte_->reinitialiserChrono();
    affichageTexte_->demarrerChrono();

	controleurLumiere_ = FacadeModele::obtenirInstance()->obtenirControleurLumiere();

	FacadeModele::obtenirInstance()->assignerEnvironnement(0);
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
	EnginSon::obtenirInstance()->stopMusique();
	controleRobot_ = nullptr;
    affichageTexte_->assignerProfilEstAffiche(false);
    affichageTexte_->assignerTempsEstAffiche(false);
    affichageTexte_->reinitialiserChrono();
    affichageTexte_->pauseChrono();
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

	controleurLumiere_->assignerLumiereAmbianteGlobale(lumiereAmbiante);
	controleurLumiere_->afficherLumiereAmbianteGlobale();
	
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
	
	controleurLumiere_->assignerLumiereDirectionnelle(lumiereDirectionnelle);
	controleurLumiere_->afficherLumiereDirectionnelle();

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
	glm::dvec3 positionRobot = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_TABLE)->chercher(ArbreRenduINF2990::NOM_ROBOT)->obtenirPositionCourante();
	controleurLumiere_->assignerLumiereSpotGyro(lumiereSpot);
	controleurLumiere_->assignerLumiereSpotRobot(lumiereSpot);

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
/// @fn void ModeSimulation::preChangementDeProfil()
///
/// Fonction appelée avant qu'il y ait changement de profil pour arrêter les accès. Arrête aussi le thread du robot.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeSimulation::preChangementDeProfil(){
	//Terminer le thread du robot et préparer à un changement au mode automatique
	controleRobot_->passerAModeManuel();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeSimulation::postChangementDeProfil()
///
/// Fonction appelée après qu'il y ait changement de profil pour repartir la simulation. Passe le robot en mode automatique.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeSimulation::postChangementDeProfil(){
	// On met à jour le profil
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	// Le robot charge la référence aux nouveaux comportements
	controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
	//Repartir le thread en mode automatique, comportement defaut
	controleRobot_->passerAModeAutomatique();
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

		case '3':
			break;

		case 'B':
			break;

		case '\b':
			controleRobot_->terminerBoucleRobot();
			controleRobot_->robot_->positionDepart();
			controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
			controleRobot_->passerAModeAutomatique();
            affichageTexte_->reinitialiserChrono();
			break;

        case VK_ESCAPE:
        {
            bool estEnPause = controleRobot_->getEnPause();
            controleRobot_->setEnPause(!estEnPause);
            if (estEnPause)
            {
                affichageTexte_->demarrerChrono();
            }
            else
            {
                affichageTexte_->pauseChrono();
            }
        }
        break;

		default:
			break;
		}

		if (!controleRobot_->getEnPause())
		{
			const bool estRepetition = ((HIWORD(lParam) & KF_REPEAT) == KF_REPEAT);
			if (!estRepetition)
			{
                CommandeRobot* commande = profil_->obtenirCommandeRobot(wParam);
                if (commande != nullptr)
                {
                    TypeCommande type = commande->obtenirTypeCommande();
                    actionsAppuyees_.at(type) = true;
                }
				controleRobot_->traiterCommande(commande, true);
			}
		}
	}
	else if (msg == WM_KEYUP)
	{
		if (!controleRobot_->getEnPause())
		{
			CommandeRobot* commandeCourante = profil_->obtenirCommandeRobot(wParam);
			if (commandeCourante != nullptr && commandeCourante->obtenirTypeCommande() != INVERSER_MODE_CONTROLE)
			{
                // Arreter les moteurs.
                std::unique_ptr<CommandeRobot> commandeArreter = std::make_unique<CommandeRobot>(ARRETER);
                controleRobot_->traiterCommande(commandeArreter.get(), true);

                // Indiquer que la commande n'est plus appuyée dans les flags d'actions appuyées
                TypeCommande type = commandeCourante->obtenirTypeCommande();
                actionsAppuyees_.at(type) = false;

                // Relancer les commandes qui sont toujours appuyées.
                for (int i = 1; i < actionsAppuyees_.size(); i++)
                {
                    if (actionsAppuyees_.at((TypeCommande)i))
                    {
                        std::unique_ptr<CommandeRobot> commandeMiseAJour  = std::make_unique<CommandeRobot>((TypeCommande)i, true);
                        controleRobot_->traiterCommande(commandeMiseAJour.get(), true);
                    }
                }
			}
		}
	}
	if (FacadeModele::obtenirInstance()->obtenirAutorisationInputSouris())
	{
		switch (msg)
		{
		case WM_RBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
			gererClicDroitEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_RBUTTONUP:
			gererClicDroitRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_MOUSEMOVE:
			gererMouvementSouris(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_MOUSEWHEEL:
			gererMoletteSouris(GET_WHEEL_DELTA_WPARAM(wParam));
			break;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////