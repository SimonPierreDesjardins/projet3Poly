///////////////////////////////////////////////////////////////////////////
/// @file ModePieces.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-03-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>

#include "ModePieces.h"
#include "Utilitaire.h"
#include "Vue.h"
#include "Projection.h"


#include "NoeudRobot.h"
#include "CommandeRobot.h"
#include "AffichageTexte.h"
#include "ControleurLumiere.h"

#include "EnginSon.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"



std::array<char, 11> ModePieces::touchesNonConfigurable_ = { { '+', '-', '\b', '1', '2', '3', 'J', 'K', 'L', 'B', 'T' } };
  
////////////////////////////////////////////////////////////////////////
///
/// @fn ModePieces::ModePieces()
///
/// Constructeur par défaut pour le mode pieces
///
////////////////////////////////////////////////////////////////////////
ModePieces::ModePieces()
{
	typeMode_ = PIECES;
	controleRobot_ = std::make_unique<ControleRobot>();
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
	// On fait démarrer le robot en mode manuel
	controleRobot_->passerAModeManuel();
    actionsAppuyees_ = { { false, false, false, false, false } };
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	table_ = arbre_->chercher(0);
	controleRobot_->obtenirNoeud()->assignerMode(typeMode_);
	visiteur_ = VisiteurDetectionRobot(controleRobot_->obtenirNoeud());
	srand(time(NULL));
	startThread();

    affichageTexte_ = FacadeModele::obtenirInstance()->obtenirAffichageTexte();
    affichageTexte_->assignerProfilEstAffiche(true);
    affichageTexte_->assignerTempsEstAffiche(true);
    affichageTexte_->reinitialiserChrono();
    affichageTexte_->demarrerChrono();

	minuterie_.reinitialiserChrono();

	controleurLumiere_ = FacadeModele::obtenirInstance()->obtenirControleurLumiere();

	FacadeModele::obtenirInstance()->assignerEnvironnement(0);

	controleurLumiere_->assignerLumiereSpotGyro(true);
	controleurLumiere_->assignerLumiereSpotRobot(true);
	controleurLumiere_->setEnPause(false);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModePieces::~ModePieces()
///
/// Destructeur de la classe ModePieces
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ModePieces::~ModePieces()
{
	profil_->setPiece(0);
	controleRobot_ = nullptr;
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
/// @fn void ModePieces::inverserLumiereAmbiante()
///
/// Fonction qui permet d'alterner l'état de la lumière ambiante 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModePieces::inverserLumiereAmbiante()
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
/// @fn void ModePieces::inverserLumiereDirectionnelle()
///
/// Fonction qui permet d'alterner l'état de la lumière directionnelle 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModePieces::inverserLumiereDirectionnelle()
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
/// @fn void ModePieces::inverserLumiereSpot()
///
/// Fonction qui permet d'alterner l'état de la lumière spot
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModePieces::inverserLumiereSpot()
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
/// @fn void ModePieces::preChangementDeProfil()
///
/// Fonction appelée avant qu'il y ait changement de profil pour arrêter les accès. Arrête aussi le thread du robot.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModePieces::preChangementDeProfil(){
	//Terminer le thread du robot et préparer à un changement au mode automatique
	controleRobot_->passerAModeManuel();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModePieces::postChangementDeProfil()
///
/// Fonction appelée après qu'il y ait changement de profil pour repartir le mode piece. Passe le robot en mode automatique.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModePieces::postChangementDeProfil(){
	// On met à jour le profil
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	// Le robot charge la référence aux nouveaux comportements
	controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
	//Repartir le thread en mode automatique, comportement defaut
	controleRobot_->passerAModeAutomatique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModePieces::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
/// Fonction qui permet de traiter les entrées utilisateur en mode simulation. 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void ModePieces::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (!FacadeModele::obtenirInstance()->obtenirAutorisationInputClavier())
		return;

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

		case 'B':
			break;

		case '\b':
			controleRobot_ = nullptr;
			controleRobot_ = std::make_unique<ControleRobot>();
			profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
			controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
			controleRobot_->passerAModeManuel();
			controleurLumiere_->assignerLumiereSpotGyro(true);
			affichageTexte_->reinitialiserChrono();
			controleRobot_->obtenirNoeud()->positionDepart();
			break;

        case VK_ESCAPE:
        {
            bool estEnPause = controleRobot_->getEnPause();
            controleRobot_->setEnPause(!estEnPause);
			controleurLumiere_->setEnPause(!estEnPause);
			modeEnPause = !modeEnPause;
            if (estEnPause)
            {
                affichageTexte_->demarrerChrono();      
            }
            else
            {
                affichageTexte_->pauseChrono();
                std::unique_ptr<CommandeRobot> commandeArreter = std::make_unique<CommandeRobot>(ARRETER);
                controleRobot_->traiterCommande(commandeArreter.get(), true);
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


////////////////////////////////////////////////////////////////////////
///
/// @fn glm::dvec3 ModePieces::genererPositionCoin() 
///
/// Fonction qui génère une position aléatoire pour la piece
///
/// @return un vecteur contenant la position
///
////////////////////////////////////////////////////////////////////////

glm::dvec3 ModePieces::genererPositionCoin() 
{

		double x = (rand() % 90) - 45;
		double y = (rand() % 44) -22;


		return{ x, y, 0.0 };


}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModePieces::postAnimer()
///
/// Fonction qui permet de visiter les noeuds et detecter collision
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void ModePieces::postAnimer()
{
	if ((int)(minuterie_.obtenirDuree()) % 15 == 0 && (int)(minuterie_.obtenirDuree()) != 0)
	{
		arbre_->chercher(0)->effacerTypeNoeud("piece");
		minuterie_.reinitialiserChrono();
		startThread();

	}
	arbre_->accepterVisiteur(&visiteur_);
	if (objectsReadyToSpawn)
	{
		spawnObjects();
	}
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ModePieces::obtenirModeEnPause()
///
/// Fonction qui permet de dire si le mode est en pause ou non
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
bool ModePieces::obtenirModeEnPause()
{
	return modeEnPause;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ModePieces::obtenirModeEnPause()
///
/// Fonction qui permet de dire si le mode est en pause ou non
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void ModePieces::creerPieces()
{
	spawnLock.lock();
	for (int i = 0; i < 10; i++)
	{
		
		noeudCoinCourant = arbre_->creerNoeud(COIN_ENTITY);
		positionNoeudCourant = genererPositionCoin();
		noeudCoinCourant->assignerPositionRelative(positionNoeudCourant);
		noeudCoinCourant->assignerPositionCourante(positionNoeudCourant);
		noeudCoinCourant->mettreAJourFormeEnglobante();
		objectsToSpawn.push_back(noeudCoinCourant);
	}
	objectsReadyToSpawn = true;
	spawnLock.unlock();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModePieces::startThread()
///
/// Fonction qui permet de partir un thread
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void ModePieces::startThread()
{
	th = std::thread(&ModePieces::creerPieces, this);
	th.detach();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModePieces::spawnObjects()
///
/// Fonction qui rajoute les pieces a l'arbre
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void ModePieces::spawnObjects()
{
	spawnLock.lock();
	for (int i = 0; i < objectsToSpawn.size(); i++)
	{
		table_->ajouter(objectsToSpawn[i]);
	}
	objectsToSpawn.clear();
	objectsReadyToSpawn = false;
	spawnLock.unlock();
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////