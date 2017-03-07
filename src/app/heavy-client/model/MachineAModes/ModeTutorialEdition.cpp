///////////////////////////////////////////////////////////////////////////
/// @file ModeTutorialEdition.cpp
/// @author Frédéric Grégoire
/// @date 2017-03-01
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////

#include "ModeTutorialEdition.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
#include "VisiteurSauvegarde.h"
#include "EtatTypes.h"
#include "NoeudRobot.h"
#include "EditionTutorialState.cs"

const int VK_KEY_W = 'W';
const int VK_KEY_A = 'A';
const int VK_KEY_Y = 'Y';
const int VK_KEY_G = 'G';
const int VK_KEY_H = 'H';
const int VK_KEY_J = 'J';
const int VK_KEY_N = 'N';
const int VK_KEY_D = 'D';
const int VK_KEY_S = 'S';
const int VK_KEY_R = 'R';
const int VK_KEY_E = 'E';
const int VK_KEY_C = 'C';
const int VK_KEY_Z = 'Z';
const int VK_KEY_T = 'T';
const int VK_KEY_P = 'P';
const int VK_KEY_L = 'L';
const int VK_KEY_M = 'M';

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTutorialEdition::ModeTutorialEdition()
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ModeTutorialEdition::ModeTutorialEdition()
{
	typeMode_ = TUTORIAL_EDITION;
	//etat_ = std::make_unique <EtatSelection>();
	etat_ = NULL;
	visiteurSuppression_ = std::make_unique<VisiteurSuppression>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTutorialEdition::~ModeTutorialEdition()
///
/// Destructeur par défaut de la classe ModeTutorialEdition
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ModeTutorialEdition::~ModeTutorialEdition()
{
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()  != nullptr) {
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->deselectionnerTout();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::gererToucheT()
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::gererToucheT()
{}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::sauvegarder()
///
/// Cette fonction permet de gérer la sauvegarde dans le ModeTutorialEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::sauvegarder()
{
	std::unique_ptr<VisiteurSauvegarde> visiteur = std::make_unique<VisiteurSauvegarde>();
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::gererToucheSupprimer()
///
/// Cette fonction permet de gérer la touche supprimer dans le ModeTutorialEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::gererToucheSupprimer()
{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->accepterVisiteur(visiteurSuppression_.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
///	Fonction qui permet de traiter les entrées utilisateur en mode test.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
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
				//etat_->gererToucheEchappe();
				break;

			case VK_OEM_PLUS:
				gererTouchePlus();
				break;

			case VK_OEM_MINUS:
				gererToucheMoins();
				break;

			case VK_KEY_D:
				if (getCurrentTutorialState() == (int)SELECT_MOVE_TOOL)
				{
					etat_ = std::make_unique<EtatDeplacement>();
				}
				break;

			case VK_KEY_S:
				// Verification de controle pour ne pas changer d'outils lors du ctrl+s
				if (getCurrentTutorialState() == (int)SELECT_TOOL)
				{
					if (!(GetKeyState(VK_CONTROL) && GetKeyState(VK_LCONTROL) && GetKeyState(VK_RCONTROL))) {
						etat_ = std::make_unique<EtatSelection>();
					}
				}
				break;

			case VK_KEY_R:
				//etat_ = std::make_unique<EtatRotation>();
				break;

			case VK_KEY_E:
				if (getCurrentTutorialState() == (int)SELECT_SCALE_TOOL)
				{
					etat_ = std::make_unique<EtatMiseAEchelle>();
				}
				break;

			case VK_KEY_C:
				if (getCurrentTutorialState() == (int)SELECT_DUPLICATE_TOOL)
				{
					etat_ = std::make_unique<EtatDuplication>();
				}
				break;

			case VK_KEY_Z:
				//etat_ = std::make_unique<EtatLoupe>();
				break;

			case VK_KEY_P:
				if (getCurrentTutorialState() == (int)SELECT_POST_TOOL)
				{
					etat_ = std::make_unique<EtatCreationPoteau>();
				}
				break;

			case VK_KEY_M:
				//etat_ = std::make_unique<EtatCreationMur>();
				break;

			case VK_KEY_L:
				//etat_ = std::make_unique<EtatCreationLigne>();
				break;

			case VK_KEY_T:
				//gererToucheT();
				break;

			case VK_DELETE:
				//gererToucheSupprimer();
				break;

			case VK_MENU:
			case VK_LMENU:
			case VK_RMENU:
				//etat_->gererToucheAltEnfoncee();
				break;

			case VK_CONTROL:
			case VK_LCONTROL:
			case VK_RCONTROL:
				//etat_->gererToucheControlEnfoncee();
				break;

			default:
				break;
			}
		}
		// Répartition du traitement des touches relachées.
		if (msg == WM_KEYUP) {
			switch (wParam) {
			case VK_MENU:
			case VK_LMENU:
			case VK_RMENU:
				//etat_->gererToucheAltRelachee();
				break;

			case VK_CONTROL:
			case VK_RCONTROL:
			case VK_LCONTROL:
				//etat_->gererToucheControlRelachee();
				break;

			default:
				break;
			}
		}
		// Répartition du traitement des touches enfoncées provenant du système pour les différents types de claviers.
		if (msg == WM_SYSKEYDOWN) {
			switch (wParam)	{
			case VK_MENU:
			case VK_LMENU:
			case VK_RMENU:
				//etat_->gererToucheAltEnfoncee();
				break;

			case VK_CONTROL:
			case VK_LCONTROL:
			case VK_RCONTROL:
				//etat_->gererToucheControlEnfoncee();
				break;
			}
		}
		// Répartition du traitement des touches relâchées provenant du système pour les différents types de claviers.
		if (msg == WM_SYSKEYUP) {
			switch (wParam) {
			case VK_MENU:
			case VK_LMENU:
			case VK_RMENU:
				//etat_->gererToucheAltRelachee();
				break;

			case VK_CONTROL:
			case VK_RCONTROL:
			case VK_LCONTROL:
				//etat_->gererToucheControlRelachee();
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
			if (etat_ != NULL)
			{
				leftClickDownWithCurrentTool(lParam);
			}
			break;

		case WM_LBUTTONUP:
			if (etat_ != NULL)
			{
				leftClickUpWithCurrentTool(lParam);
			}
			break;

		case WM_RBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
			//etat_->gererClicDroitEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_RBUTTONUP:
			//etat_->gererClicDroitRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			ChangeEditionTutorialState();
			break;

		case WM_MOUSEMOVE:
			if (etat_ != NULL)
			{
				etat_->assignerSymboleCurseur();
				etat_->gererMouvementSouris(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			}
			break;

		case WM_MOUSEWHEEL:
			//gererMoletteSouris(GET_WHEEL_DELTA_WPARAM(wParam));
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
///	Fonction qui permet de traiter les entrées utilisateur en mode test.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
int ModeTutorialEdition::getCurrentTutorialState()
{
	return currentTutorialState_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
///	Fonction qui permet de traiter les entrées utilisateur en mode test.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::setCurrentTutorialState(int newCurrentTutorialState)
{
	currentTutorialState_ = newCurrentTutorialState;
}

void ModeTutorialEdition::unselectCurrentTool()
{
	etat_ = NULL;
}

int ModeTutorialEdition::getNomberOfObjects(std::string TypeOfObject)
{
	NoeudComposite* table = static_cast<NoeudComposite*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table"));
	int objects = table->obtenirNombreEnfants();
	int numberOfObject = 0;
	for (int i = 0; i < objects; i++)
	{
		if (table->chercher(i)->obtenirType() == TypeOfObject)
		{
			numberOfObject++;
			indexOfCurrentObject_ = i;
		}
	} 
	return numberOfObject;
}

bool ModeTutorialEdition::isTutorialObjectSelect()
{
	return static_cast<NoeudComposite*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table"))->chercher(indexOfCurrentObject_)->estSelectionne();
}

double ModeTutorialEdition::getScaleOfTutorialObject()
{
	return static_cast<NoeudComposite*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table"))->chercher(indexOfCurrentObject_)->obtenirFacteurMiseAEchelle();
}

glm::dvec3 ModeTutorialEdition::getPositionOfTutorialObject()
{
	return static_cast<NoeudComposite*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table"))->chercher(indexOfCurrentObject_)->obtenirPositionCourante();
}

void ModeTutorialEdition::leftClickDownWithCurrentTool(LPARAM lParam)
{
	etat_->gererClicGaucheEnfonce(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	switch (etat_->getType())
	{
		case NONE:
		break;

		case CREATION_LIGNE:
			break;

		case CREATION_MUR:
			break;

		case DUPLICATION:
		case CREATION_POTEAU:
			numberOfObjects_ = getNomberOfObjects("poteau");
			break;

		case DEPLACEMENT:
			currentPosition_ = getPositionOfTutorialObject();
			break;

		case LOUPE:
			break;

		case MISE_A_ECHELLE:
			currentScale_ = getScaleOfTutorialObject();
			break;

		case ROTATION:
			break;

		case SELECTION:
			break;

		default:
			break;
	}
}

void ModeTutorialEdition::leftClickUpWithCurrentTool(LPARAM lParam)
{
	etat_->gererClicGaucheRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	switch (etat_->getType())
	{
	case NONE:
		break;

	case CREATION_LIGNE:
		break;

	case CREATION_MUR:
		break;

	case DUPLICATION:
	case CREATION_POTEAU:
		if (numberOfObjects_ != getNomberOfObjects("poteau"))
			ChangeEditionTutorialState();
		break;

	case DEPLACEMENT:
		if (currentPosition_ != getPositionOfTutorialObject())
			ChangeEditionTutorialState();
		break;

	case LOUPE:
		break;

	case MISE_A_ECHELLE:
		if (currentScale_ != getScaleOfTutorialObject())
			ChangeEditionTutorialState();
		break;

	case ROTATION:
		break;

	case SELECTION:
		if (isTutorialObjectSelect())
			ChangeEditionTutorialState();
		break;

	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////