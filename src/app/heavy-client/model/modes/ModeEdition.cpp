///////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <iostream>
#include "Utilitaire.h"
#include "FacadeModele.h"
#include "NetworkManager.h"
#include "Vue.h"
#include "Projection.h"
#include "VisiteurSauvegarde.h"
#include "EtatTypes.h"
#include "NoeudRobot.h"

#include "ModeEdition.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeEdition::ModeEdition()
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ModeEdition::ModeEdition(engine::SimulationEngine* engine, client_network::MapSession* mapSession)
	: OnlineMapMode(mapSession),
	  visiteurSuppression_(mapSession)
{
	typeMode_ = OFFLINE_EDITION;
	assignerEtat(SELECTION);

	engine->setEnvironnement(2);
	tree_ = engine->getEntityTree();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeEdition::~ModeEdition()
///
/// Destructeur par défaut de la classe ModeEdition
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ModeEdition::~ModeEdition()
{
	mapSession_->requestToLeaveMapSession();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheT()
///
/// Cette fonction permet de gérer la touche T dans le modeEdition.
///
/// Elle assigne le mode TEST à l'instance obtenue.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheT()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::sauvegarder()
///
/// Cette fonction permet de gérer la sauvegarde dans le modeEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::sauvegarder()
{
	std::unique_ptr<VisiteurSauvegarde> visiteur = std::make_unique<VisiteurSauvegarde>();
	tree_->accepterVisiteur(visiteur.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheSupprimer()
///
/// Cette fonction permet de gérer la touche supprimer dans le modeEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheSupprimer()
{
	tree_->accepterVisiteur(&visiteurSuppression_);
}

/// Modifie l'etat courant.
void ModeEdition::assignerEtat(Tool etat)
{
	switch(etat)
	{
	case SELECTION:
		etat_ = std::move(std::make_unique<EtatSelection>(mapSession_));
		break;

	case DEPLACEMENT:
		etat_ = std::move(std::make_unique<EtatDeplacement>(mapSession_));
		break;

	case ROTATION:
		etat_ = std::move(std::make_unique<EtatRotation>(mapSession_));
		break;

	case MISE_A_ECHELLE:
		etat_ = std::move(std::make_unique<EtatMiseAEchelle>(mapSession_));
		break;
	
	case DUPLICATION:
		etat_ = std::move(std::make_unique<EtatDuplication>(mapSession_));
		break;

	case CREATION_POTEAU:
		etat_ = std::move(std::make_unique<EtatCreationPoteau>(mapSession_));
		break;

	case CREATION_MUR:
		etat_ = std::move(std::make_unique<EtatCreationMur>(mapSession_));
		break;
	
	case CREATION_LIGNE_NOIRE:
		etat_ = std::move(std::make_unique<EtatCreationLigne>(mapSession_));
		break;
	
	case LOUPE:
		etat_ = std::move(std::make_unique<EtatLoupe>());
		break;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
///	Fonction qui permet de traiter les entrées utilisateur en mode test.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	bool autoriserInput = FacadeModele::obtenirInstance()->obtenirAutorisationInputClavier();


	if (autoriserInput) {
		if (msg == WM_KEYDOWN) {
			switch (wParam) {

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

			case VK_ESCAPE:
				etat_->gererToucheEchappe();
				break;

			case VK_OEM_PLUS:
				gererTouchePlus();
				break;

			case VK_OEM_MINUS:
				gererToucheMoins();
				break;

			case VK_KEY_D:
				assignerEtat(DEPLACEMENT);
				break;

			case VK_KEY_S:
				// Verification de controle pour ne pas changer d'outils lors du ctrl+s
				if (!(GetKeyState(VK_CONTROL) && GetKeyState(VK_LCONTROL) && GetKeyState(VK_RCONTROL))) {
					assignerEtat(SELECTION);
				}
				break;

			case VK_KEY_R:
				assignerEtat(ROTATION);
				break;

			case VK_KEY_E:
				assignerEtat(MISE_A_ECHELLE);
				break;

			case VK_KEY_C:
				assignerEtat(DUPLICATION);
				break;

			case VK_KEY_Z:
				assignerEtat(LOUPE);
				break;

			case VK_KEY_P:
				assignerEtat(CREATION_POTEAU);
				break;

			case VK_KEY_O:
				etat_ = std::make_unique<EtatCreationTeleporteur>();
				break;

			case VK_KEY_M:
				assignerEtat(CREATION_MUR);
				break;

			case VK_KEY_L:
				assignerEtat(CREATION_LIGNE_NOIRE);
				break;

			case VK_KEY_T:
				gererToucheT();
				break;

			case VK_DELETE:
				gererToucheSupprimer();
				break;

			case VK_MENU:
				// Poursuivre.
			case VK_LMENU:
				// Poursuivre.
			case VK_RMENU:
				etat_->gererToucheAltEnfoncee();
				break;

			case VK_CONTROL:
				// Poursuivre.
			case VK_LCONTROL:
				// Poursuivre.
			case VK_RCONTROL:
				// Poursuivre.
				etat_->gererToucheControlEnfoncee();
				break;

			default:
				break;
			}
		}
		// Répartition du traitement des touches relachées.
		if (msg == WM_KEYUP) {
			switch (wParam) {
			case VK_MENU:
				// Poursuivre.
			case VK_LMENU:
				// Poursuivre.
			case VK_RMENU:
				etat_->gererToucheAltRelachee();
				break;

			case VK_CONTROL:
				// Poursuivre.
			case VK_RCONTROL:
				// Poursuivre.
			case VK_LCONTROL:
				etat_->gererToucheControlRelachee();
				break;

			default:
				break;
			}
		}
		// Répartition du traitement des touches enfoncées provenant du système pour les différents types de claviers.
		if (msg == WM_SYSKEYDOWN) {
			switch (wParam)	{
			case VK_MENU:
				// Poursuivre.
			case VK_LMENU:
				// Poursuivre.
			case VK_RMENU:
				etat_->gererToucheAltEnfoncee();
				break;

			case VK_CONTROL:
				// Poursuivre.
			case VK_LCONTROL:
				// Poursuivre.
			case VK_RCONTROL:
				etat_->gererToucheControlEnfoncee();
				break;
			}
		}
		// Répartition du traitement des touches relâchées provenant du système pour les différents types de claviers.
		if (msg == WM_SYSKEYUP) {
			switch (wParam) {
			case VK_MENU:
				// Poursuivre.
			case VK_LMENU:
				// Poursuivre.
			case VK_RMENU:
				etat_->gererToucheAltRelachee();
				break;

			case VK_CONTROL:
				// Poursuivre.
			case VK_RCONTROL:
				// Poursuivre.
			case VK_LCONTROL:
				etat_->gererToucheControlRelachee();
				break;
			}
		}
	}
	// Répartition du traitement des messages provenant de la souris.
	if (FacadeModele::obtenirInstance()->obtenirAutorisationInputSouris()) 
	{
		switch (msg)
		{
		case WM_LBUTTONDBLCLK:
		case WM_LBUTTONDOWN:
			etat_->gererClicGaucheEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_LBUTTONUP:
			etat_->gererClicGaucheRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_RBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
			etat_->gererClicDroitEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_RBUTTONUP:
			etat_->gererClicDroitRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_MOUSEMOVE:
			etat_->assignerSymboleCurseur();
			etat_->gererMouvementSouris(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
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