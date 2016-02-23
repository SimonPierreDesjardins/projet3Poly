///////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeEdition.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
#include "VisiteurSauvegarde.h"
#include "EtatTypes.h"
#include "NoeudRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeEdition::ModeEdition()
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ModeEdition::ModeEdition()
{
	typeMode_ = EDITION;
	etat_ = make_unique <EtatSelection>();
	visiteurSuppression_ = std::make_unique<VisiteurSuppression>();
	/*std::shared_ptr<noeudabstrait> robot = facademodele::obtenirinstance()->obtenirarbrerenduinf2990()->creernoeud(arbrerenduinf2990::nom_robot);
	facademodele::obtenirinstance()->obtenirarbrerenduinf2990()->ajouter(robot);*/
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
/// @fn void ModeEdition::gererTouchePlus()
///
/// Cette fonction permet de gérer la touche + dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom in.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererTouchePlus()
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
void ModeEdition::gererToucheMoins()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	}
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
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

void ModeEdition::gererToucheY()
{
	float vitesse = 30;
	NoeudAbstrait* robot = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0)->chercher(ArbreRenduINF2990::NOM_ROBOT);
	robot->assignerVitesseDroite(vitesse);
	robot->assignerVitesseGauche(vitesse);
}

void ModeEdition::gererToucheG()
{
	float vitesse = 30;
	NoeudAbstrait* robot = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0)->chercher(ArbreRenduINF2990::NOM_ROBOT);
	robot->assignerVitesseDroite(vitesse);
	robot->assignerVitesseGauche(-vitesse);
}

void ModeEdition::gererToucheH()
{
	float vitesse = 30;
	NoeudAbstrait* robot = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0)->chercher(ArbreRenduINF2990::NOM_ROBOT);
	robot->assignerVitesseDroite(-vitesse);
	robot->assignerVitesseGauche(-vitesse);
}

void ModeEdition::gererToucheJ()
{
	float vitesse = 30;
	NoeudAbstrait* robot = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0)->chercher(ArbreRenduINF2990::NOM_ROBOT);
	robot->assignerVitesseDroite(-vitesse);
	robot->assignerVitesseGauche(vitesse);
}

void ModeEdition::gererToucheN()
{
	float vitesse = 0;
	NoeudAbstrait* robot = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0)->chercher(ArbreRenduINF2990::NOM_ROBOT);
	robot->assignerVitesseDroite(0);
	robot->assignerVitesseGauche(0);
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

void ModeEdition::gererFlecheGauche()
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
void ModeEdition::gererFlecheBas()
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
void ModeEdition::gererFlecheHaut()
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
void ModeEdition::gererFlecheDroit()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(-10, 0);
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
	unique_ptr<VisiteurSauvegarde> visiteur = make_unique<VisiteurSauvegarde>();
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::sauvegarder()
///
/// Cette fonction permet de gérer le chargement dans le modeEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::charger()
{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chargerZone();
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererMoletteSouris(const int & delta)
///
/// Cette fonction permet de gérer la molette de le souris dans le modeEdition.
///
/// Selon le signe du delta, nous ferons un zoom in ou out.
///
///@param[in] delta : La différence entre du mouvement de molette de la souris.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererMoletteSouris(const int& delta)
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	}
	else {
		if (delta > 0) {
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
		}
		else {
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
		}
	}
}

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
				etat_ = make_unique<EtatDeplacement>();
				break;

			case VK_KEY_S:
				// Verification de controle pour ne pas changer d'outils lors du ctrl+s
				if (!(GetKeyState(VK_CONTROL) && GetKeyState(VK_LCONTROL) && GetKeyState(VK_RCONTROL))) {
					etat_ = make_unique<EtatSelection>();
				}
				break;

			case VK_KEY_R:
				etat_ = make_unique<EtatRotation>();
				break;

			case VK_KEY_E:
				etat_ = make_unique<EtatMiseAEchelle>();
				break;

			case VK_KEY_C:
				etat_ = make_unique<EtatDuplication>();
				break;

			case VK_KEY_Z:
				etat_ = make_unique<EtatLoupe>();
				break;

			case VK_KEY_P:
				etat_ = make_unique<EtatCreationPoteau>();
				break;

			case VK_KEY_M:
				etat_ = make_unique<EtatCreationMur>();
				break;

			case VK_KEY_L:
				etat_ = make_unique<EtatCreationLigne>();
				break;

			case VK_KEY_T:
				gererToucheT();
				break;

			case VK_KEY_Y:
				gererToucheY();
				break;

			case VK_KEY_G:
				gererToucheG();
				break;
			case VK_KEY_H:
				gererToucheH();
				break;

			case VK_KEY_J:
				gererToucheJ();
				break;

			case VK_KEY_N:
				gererToucheN();
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
	if (FacadeModele::obtenirInstance()->obtenirAutorisationInputSouris()) {
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