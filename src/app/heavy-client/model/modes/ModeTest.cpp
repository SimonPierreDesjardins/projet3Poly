///////////////////////////////////////////////////////////////////////////
/// @file ModeTest.cpp
/// @author Fr�d�ric Gr�goire
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

std::array<char, 11> ModeTest::touchesNonConfigurable_ = { { '+', '-', '\b', '1', '2', '3', 'J', 'K', 'L', 'B', 'T' } };

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTest::ModeTest()
///
/// Constructeur par d�faut pour le mode test
///
////////////////////////////////////////////////////////////////////////
ModeTest::ModeTest(client_network::ClientMapSession* mapSession)
	: OnlineMapMode(mapSession)
{
	typeMode_ = TEST;
	//profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	//controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
	//visiteur_ = VisiteurDetectionRobot(controleRobot_->obtenirNoeud());
	//arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	// On fait d�marrer le robot en mode automatique
	//controleRobot_->passerAModeManuel();
    actionsAppuyees_ = { { false, false, false, false, false } };

    affichageTexte_ = FacadeModele::obtenirInstance()->obtenirAffichageTexte();
    affichageTexte_->assignerProfilEstAffiche(true);
    affichageTexte_->assignerTempsEstAffiche(true);
    affichageTexte_->reinitialiserChrono();
    affichageTexte_->demarrerChrono();

	//FacadeModele::obtenirInstance()->assignerEnvironnement(1);

	controleurLumiere_ = FacadeModele::obtenirInstance()->obtenirControleurLumiere();
	controleurLumiere_->assignerLumiereSpotGyro(true);
	controleurLumiere_->assignerLumiereSpotRobot(true);
	controleurLumiere_->setEnPause(false);

	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	//controleRobot_ = std::make_unique<ControleRobot>(arbre, profil_, controleurLumiere_, mapSession);
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
	//controleRobot_ = nullptr;
    affichageTexte_->assignerProfilEstAffiche(false);
    affichageTexte_->assignerTempsEstAffiche(false);
    affichageTexte_->reinitialiserChrono();
    affichageTexte_->pauseChrono();
	controleurLumiere_->assignerLumiereAmbianteGlobale(true);
	controleurLumiere_->assignerLumiereDirectionnelle(true);
	controleurLumiere_->assignerLumiereSpotGyro(false);
	controleurLumiere_->assignerLumiereSpotRobot(false);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTest::preChangementDeProfil()
///
/// Fonction appel�e avant qu'il y ait changement de profil pour arr�ter les acc�s. Arr�te aussi le thread du robot.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::preChangementDeProfil(){
	//Terminer le thread du robot et pr�parer � un changement au mode automatique
	//controleRobot_->passerAModeManuel();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTest::postChangementDeProfil()
///
/// Fonction appel�e apr�s qu'il y ait changement de profil pour repartir la simulation. Passe le robot en mode automatique.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::postChangementDeProfil(){
	//Repartir le thread en mode automatique, comportement defaut
	//controleRobot_->passerAModeAutomatique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeSimulation::inverserLumiereAmbiante()
///
/// Fonction qui permet d'alterner l'�tat de la lumi�re ambiante 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::inverserLumiereAmbiante()
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
/// Fonction qui permet d'alterner l'�tat de la lumi�re directionnelle 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::inverserLumiereDirectionnelle()
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
/// Fonction qui permet d'alterner l'�tat de la lumi�re spot
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::inverserLumiereSpot()
{
	lumiereSpot = !lumiereSpot;
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
/// @fn ModeTest::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
/// Fonction qui permet de traiter les entr�es utilisateur en mode test. 
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

		case 'B':
			break;

		case '\b':
			//controleRobot_ = nullptr;
			//controleRobot_ = std::make_unique<ControleRobot>();
			//profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
			//controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
			//controleRobot_->passerAModeManuel();
			controleurLumiere_->assignerLumiereSpotGyro(true);
            affichageTexte_->reinitialiserChrono();
			//controleRobot_->robot_->positionDepart();
			break;

        case VK_ESCAPE:
        {
			/*
            //bool estEnPause = controleRobot_->getEnPause();
            //controleRobot_->setEnPause(!estEnPause);
			//controleurLumiere_->setEnPause(!estEnPause);
            if (estEnPause)
            {
                affichageTexte_->demarrerChrono();
            }
            else 
            {
                affichageTexte_->pauseChrono();
                std::unique_ptr<CommandeRobot> commandeArreter = std::make_unique<CommandeRobot>(ARRETER);
                //controleRobot_->traiterCommande(commandeArreter.get(), true);
            }
			*/
			break;
        }

		default:
			break;
		}

		/*
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
		*/
	}
	else if (msg == WM_KEYUP)
	{
		/*
		if (!controleRobot_->getEnPause())
		{
			CommandeRobot* commandeCourante = profil_->obtenirCommandeRobot(wParam);
			if (commandeCourante != nullptr && commandeCourante->obtenirTypeCommande() != INVERSER_MODE_CONTROLE)
			{
                // Arreter les moteurs.
                std::unique_ptr<CommandeRobot> commandeArreter = std::make_unique<CommandeRobot>(ARRETER);
                controleRobot_->traiterCommande(commandeArreter.get(), true);

                // Indiquer que la commande n'est plus appuy�e dans les flags d'actions appuy�es
                TypeCommande type = commandeCourante->obtenirTypeCommande();
                actionsAppuyees_.at(type) = false;

                // Relancer les commandes qui sont toujours appuy�es.
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
		*/
	}
	// R�partition du traitement des messages provenant de la souris.
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTest::postAnimer()
///
/// Fonction qui permet de visiter les noeuds et detecter collision
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void ModeTest::postAnimer()
{
	//arbre_->accepterVisiteur(&visiteur_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ModeTest::obtenirModeEnPause()
///
/// Fonction qui permet de dire si le mode est en pause ou non
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
bool ModeTest::obtenirModeEnPause()
{
	return modeEnPause;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////