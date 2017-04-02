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
////////////////////////////////////////////////////////////////////////
ModeTutorialEdition::ModeTutorialEdition(client_network::MapSession * mapSession)
	: OnlineMapMode(mapSession),
	  visiteurSuppression_(mapSession)
{
	typeMode_ = TUTORIAL_EDITION;
	etat_ = std::make_unique<EtatAbstrait>();

	table_ = static_cast<NoeudComposite*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table"));
	startIndexOfTutorialObjects_ = static_cast<NoeudComposite*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table"))->obtenirNombreEnfants();
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
/// @fn void ModeTutorialEdition::gererToucheSupprimer()
///
/// Cette fonction permet de gérer la touche supprimer dans le ModeTutorialEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::gererToucheSupprimer()
{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->accepterVisiteur(&visiteurSuppression_);
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
				if (getCurrentTutorialState() == (int)CREATING_WALL || getCurrentTutorialState() == (int)CREATING_LINE)
				{
					etat_->gererToucheEchappe();
				}
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
					etat_ = std::make_unique<EtatDeplacement>(mapSession_);
					currentPosition_ = getPositionOfTutorialObject();
				}
				break;

			case VK_KEY_S:
				// Verification de controle pour ne pas changer d'outils lors du ctrl+s
				if (getCurrentTutorialState() == (int)SELECT_TOOL)
				{
					if (!(GetKeyState(VK_CONTROL) && GetKeyState(VK_LCONTROL) && GetKeyState(VK_RCONTROL))) {
						etat_ = std::make_unique<EtatSelection>(mapSession_);
					}
				}
				break;

			case VK_KEY_R:
				if (getCurrentTutorialState() == (int)SELECT_ROTATION_TOOL)
				{
					etat_ = std::make_unique<EtatRotation>(mapSession_);
					currentObjectAttribut_ = getRotationOfTutorialObject();
				}
				break;

			case VK_KEY_E:
				if (getCurrentTutorialState() == (int)SELECT_SCALE_TOOL)
				{
					etat_ = std::make_unique<EtatMiseAEchelle>(mapSession_);
					currentObjectAttribut_ = getScaleOfTutorialObject();
				}
				break;

			case VK_KEY_C:
				if (getCurrentTutorialState() == (int)SELECT_DUPLICATE_TOOL)
				{
					etat_ = std::make_unique<EtatDuplication>(mapSession_);
					numberOfObjects_ = getNomberOfObjects("mur");
				}
				break;

			case VK_KEY_Z:
				//etat_ = std::make_unique<EtatLoupe>();
				break;

			case VK_KEY_P:
				if (getCurrentTutorialState() == (int)SELECT_POST_TOOL)
				{
					etat_ = std::make_unique<EtatCreationPoteau>(mapSession_);
					numberOfObjects_ = getNomberOfObjects("poteau");

				}
				break;

			case VK_KEY_M:
				if (getCurrentTutorialState() == (int)SELECT_WALL_TOOL)
				{
					etat_ = std::make_unique<EtatCreationMur>(mapSession_);
					numberOfObjects_ = getNomberOfObjects("mur");
				}
				break;

			case VK_KEY_L:
				if (getCurrentTutorialState() == (int)SELECT_LINE_TOOL)
				{
					etat_ = std::make_unique<EtatCreationLigne>(mapSession_);
					numberOfObjects_ = getNomberOfObjects("ligneNoire");
				}
				break;

			case VK_DELETE:
				if (getCurrentTutorialState() == (int)DELETE_TOOL)
				{
					gererToucheSupprimer();
				}
				break;

			case VK_MENU:
			case VK_LMENU:
			case VK_RMENU:
				//etat_->gererToucheAltEnfoncee();
				break;

			case VK_CONTROL:
			case VK_LCONTROL:
			case VK_RCONTROL:
				if (getCurrentTutorialState() == (int)CREATING_LINE)
				{
					etat_->gererToucheControlEnfoncee();
				}
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
				if (getCurrentTutorialState() == (int)CREATING_LINE)
				{
					etat_->gererToucheControlRelachee();
				}
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
				if (getCurrentTutorialState() == (int)CREATING_LINE)
				{
					etat_->gererToucheControlEnfoncee();
				}
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
				if (getCurrentTutorialState() == (int)CREATING_LINE)
				{
					etat_->gererToucheControlRelachee();
				}
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
			leftClickUpWithCurrentTool(lParam);
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

////////////////////////////////////////////////////////////////////////
///
/// @fn int ModeTutorialEdition::getCurrentTutorialState()
///
///	Fonction qui permet de retourner l'état du tutoriel édition. La valeur
/// retourné est un int représentant un état dans l'enum EditionTutorial State
///
/// @return int: L'état du tutoriel édition.
///
////////////////////////////////////////////////////////////////////////
int ModeTutorialEdition::getCurrentTutorialState()
{
	return currentTutorialState_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::setCurrentTutorialState(int newCurrentTutorialState)
///
///	Fonction qui permet d'assigner l'état courant du tutoriel édition.
///
/// @param int newCurrentTutorialState: état du tutoriel
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::setCurrentTutorialState(int newCurrentTutorialState)
{
	currentTutorialState_ = newCurrentTutorialState;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::unselectCurrentTool()
///
///	Désélectionne l'outil courant en utilisant le pointeur d'état vers un EtatAbstrait
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::unselectCurrentTool()
{
	etat_ = std::make_unique <EtatAbstrait>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int ModeTutorialEdition::getNomberOfObjects(std::string TypeOfObject)
///
///	Fonction qui permet de compter le nombre d'objets d'un type présent sur la table
///
/// @param std::string TypeOfObject: nom de l'objet à compter
/// @return int: Le nombre de fois qu'on objet est sur la table
///
////////////////////////////////////////////////////////////////////////
int ModeTutorialEdition::getNomberOfObjects(std::string TypeOfObject)
{
	int objects = table_->obtenirNombreEnfants();
	int numberOfObject = 0;
	for (int i = 0; i < objects; i++)
	{
		if (table_->chercher(i)->obtenirNom() == TypeOfObject)
		{
			numberOfObject++;
			indexOfCurrentObject_ = i;
		}
	} 
	return numberOfObject;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ModeTutorialEdition::isTutorialObjectSelect()
///
///	Fonction qui permet de savoir si le dernier objet créé est sélectionné.
///
/// @return bool: True si l'objet est sélectionné, false sinon.
///
////////////////////////////////////////////////////////////////////////
bool ModeTutorialEdition::isTutorialObjectSelect()
{
	return table_->chercher(indexOfCurrentObject_)->estSelectionne();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double ModeTutorialEdition::getScaleOfTutorialObject()
///
///	Fonction qui permet de savoir le facteur de dimension du dernier objet créé.
///
/// @return double: Le facteur de dimension.
///
////////////////////////////////////////////////////////////////////////
double ModeTutorialEdition::getScaleOfTutorialObject()
{
	return table_->chercher(indexOfCurrentObject_)->getPhysicsComponent().scale.x;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double ModeTutorialEdition::getRotationOfTutorialObject()
///
///	Fonction qui permet de savoir le facteur de rotation du dernier objet créé.
///
/// @return double: Le facteur de rotation.
///
////////////////////////////////////////////////////////////////////////
double ModeTutorialEdition::getRotationOfTutorialObject()
{
	return table_->chercher(indexOfCurrentObject_)->getPhysicsComponent().rotation.z;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn glm::dvec3 ModeTutorialEdition::getPositionOfTutorialObject()
///
///	Fonction qui permet de savoir la position du dernier objet créé.
///
/// @return glm::dvec3: La position de l'objet.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 ModeTutorialEdition::getPositionOfTutorialObject()
{
	return table_->chercher(indexOfCurrentObject_)->getPhysicsComponent().absolutePosition;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::selectAllTutorialObjects()
///
///	Fonction qui permet de sélectionner tous les objets créés lors du tutoriel.
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::selectAllTutorialObjects()
{
	UnselectAllObjects();
	int objects = table_->obtenirNombreEnfants();
	for (int i = startIndexOfTutorialObjects_; i < objects; i++)
	{
		table_->chercher(i)->selectionnerTout();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTutorialEdition::leftClickUpWithCurrentTool(LPARAM lParam)
///
///	Fonction qui permet de gérer le clique gauche relâché en fonction de l'outil
///
/// @param LPARAM lParam: Paramètre de la souris
///
////////////////////////////////////////////////////////////////////////
void ModeTutorialEdition::leftClickUpWithCurrentTool(LPARAM lParam)
{
	etat_->gererClicGaucheRelache(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	switch (etat_->getType())
	{
		case CREATION_LIGNE_NOIRE:
		{
			EtatCreationLigne* creationLineTool(static_cast<EtatCreationLigne*>(etat_.get()));
			if (!creationLineTool->isInCreation())
			{
				if (numberOfObjects_ != getNomberOfObjects("ligneNoire"))
					ChangeEditionTutorialState();
			}
		}
		break;

		case CREATION_MUR:
		{
			EtatCreationMur* creationWallTool(static_cast<EtatCreationMur*>(etat_.get()));
			if (!creationWallTool->isInCreation())
			{
				if (numberOfObjects_ != getNomberOfObjects("mur"))
					ChangeEditionTutorialState();
			}
		}
		break;

		case CREATION_POTEAU:
			if (numberOfObjects_ != getNomberOfObjects("poteau"))
				ChangeEditionTutorialState();
			break;

		case DEPLACEMENT:
			if (currentPosition_ != getPositionOfTutorialObject())
				ChangeEditionTutorialState();
			break;

		case DUPLICATION:
			if (numberOfObjects_ != getNomberOfObjects("mur"))
				ChangeEditionTutorialState();
			break;

		case LOUPE:
			break;

		case MISE_A_ECHELLE:
			if (currentObjectAttribut_ != getScaleOfTutorialObject())
				ChangeEditionTutorialState();
			break;

		case ROTATION:
			if (currentObjectAttribut_ != getRotationOfTutorialObject())
				ChangeEditionTutorialState();
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