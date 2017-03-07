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
ModeEdition::ModeEdition()
{
	typeMode_ = EDITION;
	etat_ = std::make_unique <EtatSelection>();
	visiteurSuppression_ = std::make_unique<VisiteurSuppression>();

	FacadeModele::obtenirInstance()->assignerEnvironnement(2);
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
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()  != nullptr) {
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->deselectionnerTout();
	}
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
	//FacadeModele::obtenirInstance()->assignerMode(TEST);
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
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur.get());
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
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->accepterVisiteur(visiteurSuppression_.get());
}

/// Modifie l'etat courant.
void ModeEdition::assignerEtat(EtatType etat)
{
	switch(etat)
	{
	case SELECTION:
		etat_ = std::make_unique<EtatSelection>();
		break;

	case DEPLACEMENT:
		etat_ = std::make_unique<EtatDeplacement>();
		break;

	case ROTATION:
		etat_ = std::make_unique<EtatRotation>();
		break;

	case MISE_A_ECHELLE:
		etat_ = std::make_unique<EtatMiseAEchelle>();
		break;
	
	case DUPLICATION:
		etat_ = std::make_unique<EtatDuplication>();
		break;

	case CREATION_POTEAU:
		etat_ = std::make_unique<EtatCreationPoteau>();
		break;

	case CREATION_MUR:
		etat_ = std::make_unique<EtatCreationMur>();
		break;
	
	case CREATION_LIGNE_NOIRE:
		etat_ = std::make_unique<EtatCreationLigne>();
		break;
	
	case ZOOM:
		etat_ = std::make_unique<EtatLoupe>();
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
				etat_ = std::make_unique<EtatDeplacement>();
				break;

			case VK_KEY_S:
				// Verification de controle pour ne pas changer d'outils lors du ctrl+s
				if (!(GetKeyState(VK_CONTROL) && GetKeyState(VK_LCONTROL) && GetKeyState(VK_RCONTROL))) {
					etat_ = std::make_unique<EtatSelection>();
				}
				break;

			case VK_KEY_R:
				etat_ = std::make_unique<EtatRotation>();
				break;

			case VK_KEY_E:
				etat_ = std::make_unique<EtatMiseAEchelle>();
				break;

			case VK_KEY_C:
				etat_ = std::make_unique<EtatDuplication>();
				break;

			case VK_KEY_Z:
				etat_ = std::make_unique<EtatLoupe>();
				break;

			case VK_KEY_P:
				etat_ = std::make_unique<EtatCreationPoteau>();
				break;

			case VK_KEY_M:
				etat_ = std::make_unique<EtatCreationMur>();
				break;

			case VK_KEY_L:
				etat_ = std::make_unique<EtatCreationLigne>();
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