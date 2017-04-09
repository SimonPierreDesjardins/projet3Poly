///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

// Commentaire Doxygen mis sur la premi�re page de la documentation Doxygen.
/**

@mainpage Projet int�grateur de deuxi�me ann�e -- INF2990

*/

#include <windows.h>
#include <cassert>
#include "wtypes.h"
#include <iostream>

#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"

#include "VueOrtho.h"
#include "VueOrbite.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, �t� 2011
#include "tinyxml2.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "EtatTypes.h"
#include "ModeTypes.h"

#include "EnginSon.h"

/// Pointeur vers l'instance unique de la classe.
std::unique_ptr<FacadeModele> FacadeModele::instance_{ nullptr };

/// Cha�ne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };

/// Constructeur par d�faut.
FacadeModele::FacadeModele()
	: network_(&eventHandler_), mapSessionManager_(&engine_, &network_), saves_(&profil_)
{}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas �t� cr��e, elle la cr�e.  Cette
/// cr�ation n'est toutefois pas n�cessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa cr�ation.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_.get() == nullptr)
	{
		instance_ = std::unique_ptr<FacadeModele>(new FacadeModele());
	}
	return instance_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction lib�re l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur lib�re les objets du mod�le.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	mode_.reset(nullptr);
	libererOpenGL();
}

void FacadeModele::initialize(HWND hWnd)
{
	engine_.initializeRendering(hWnd, &profil_);

	assignerMode(MENU_PRINCIPAL);

	// Cr�ation du module qui g�re l'affichage du texte avec OpenGL.
	eventHandler_.setNetworkManager(&network_);
	eventHandler_.setEntityTree(engine_.getEntityTree());
	eventHandler_.setMapSessionManager(&mapSessionManager_);
}

void FacadeModele::repartirMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN || msg == WM_KEYUP)
	{
		if (autorisationInputClavier_)
		{
			mode_->gererMessage(msg, wParam, lParam);
		}
	}
	else
	{
		if (autorisationInputSouris_)
		{
			mode_->gererMessage(msg, wParam, lParam);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction lib�re le contexte OpenGL et d�sinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	engine_.free();
}

//Assigne les parametres pour la vue ortho
void FacadeModele::assignerVueOrtho()
{
	engine_.setOrthoView();
}

//Assigne les parametres pour la vue orbite
void FacadeModele::assignerVueOrbite()
{
	engine_.setOrbitalView();
}

void FacadeModele::assignerVueOrbitePerso()
{
	engine_.setCloseOrbitalView();
}

//Assigne les parametres pour la vue � la premi�re personne
void FacadeModele::assignerVuePremierePersonne()
{
	engine_.setFirstPersonView(engine_.getEntityTree()->chercher(profil_.getModele()));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la sc�ne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher()
{
	engine_.render();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction r�initialise la sc�ne � un �tat "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// R�initialisation de la sc�ne.
	engine_.getEntityTree()->initialiser();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les diff�rents calculs d'animations
/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	engine_.animate(temps);
	if (engine_.isAnimating()) {
		mode_->postAnimer(temps);
	}
}

void FacadeModele::setOnlineMapMode(Mode mode, client_network::ClientMapSession* mapSession)
{
	switch (mode)
	{
	case EDITION:
		mode_ = std::make_unique<ModeEdition>(&engine_, mapSession);
		break;

	case SIMULATION:
		mode_ = std::make_unique<ModeSimulation>(&engine_, &profil_, mapSession);
		break;
	}
	continuerAffichage();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerMode(Mode mode)
///
/// Cette fonction change l'attribut mode_ pour la valeur du mode en param�tre.
///
/// @param[in] etat : Nouveau mode � traiter.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerMode(Mode mode)
{
	switch (mode) 
	{
		case MENU_PRINCIPAL:
			mapSessionManager_.requestToLeaveCurrentMapSession();
			mode_ = std::make_unique<ModeMenuPrincipal>();
			break;

		case SIMULATION:
			mode_ = std::make_unique<ModeSimulation>(&engine_, &profil_, mapSessionManager_.getCurrentMapSession());
			break;

		case EDITION:
			mode_ = std::make_unique<ModeEdition>(&engine_, mapSessionManager_.getCurrentMapSession());
			break;

		case CONFIGURE:
			mode_ = std::make_unique<ModeConfigure>();
			break;

		case TEST:
			mode_ = std::make_unique<ModeSimulation>(&engine_, &profil_, mapSessionManager_.getCurrentMapSession());
			break;

		case PERSONALIZE:
			mode_ = std::make_unique<ModePersonalize>(&engine_, &profil_);
			break;

		case TUTORIAL_EDITION:
			mode_ = std::make_unique<ModeTutorialEdition>(mapSessionManager_.getCurrentMapSession());
			break;
		
		case PIECES:
			mode_ = std::make_unique<ModePieces>(&engine_, &profil_, mapSessionManager_.getCurrentMapSession());
			break;

		default:
			break;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::continuerAffichage()
///
/// Cette fonction assigne la valeur d'un bool�an � vrai si l'on veut
/// continuer a afficher l'animation
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::continuerAffichage()
{
	engine_.resumeRendering();
}

void FacadeModele::assignerEnvironnement(int noEnviro)
{
	engine_.setEnvironnement(noEnviro);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::stopAffichage()
///
/// Cette fonction assigne la valeur d'un bool�an � false si l'on veut
/// arr�ter d'afficher l'animation
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::stopAffichage()
{
	engine_.stopRendering();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::getDesktopResolution(int& horizontal, int& vertical)
///
/// Cette fonction retourne la largeur et la hauteur de l'�cran
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::getDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerAngleRotation(double angle)
///
/// Cette fonction assigne un angle de rotation � un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: l'angle a assigner a l'objet
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerAngleRotation(const double& angle)
{
	NoeudAbstrait* table = engine_.getEntityTree()->chercher(0);
	if (table)
	{
		std::unique_ptr<VisiteurRotation> visiteurRotation = std::make_unique <VisiteurRotation>(mapSessionManager_.getCurrentMapSession());
		std::unique_ptr<VisiteurVerificationQuad> visiteurVerification = std::make_unique <VisiteurVerificationQuad>();

		unsigned int nEnfants = table->obtenirNombreEnfants();
		for (unsigned int i = 0; i < nEnfants; i++) {
			NoeudAbstrait* enfant = table->chercher(i);
			if (enfant->estSelectionne())
			{
				double angleAvantChangement = enfant->getPhysicsComponent().rotation.z;
				visiteurRotation->assignerAngleRotation(angle - angleAvantChangement);
				visiteurRotation->rotateSelectedObjects(engine_.getEntityTree());

				engine_.getEntityTree()->accepterVisiteur(visiteurVerification.get());
				bool positionValide = visiteurVerification->objetsDansZoneSimulation();
				if (!positionValide)
				{
					visiteurRotation->assignerAngleRotation(angleAvantChangement - angle);
					visiteurRotation->rotateSelectedObjects(engine_.getEntityTree());
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerFacteurGrandeur(double facteurMiseAEchelle)
///
/// Cette fonction assigne un facteur de mise � �chelle � un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: facteur de mise � �chelle
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerFacteurMiseAEchelle(const double& facteurMiseAEchelle)
{
	NoeudAbstrait* table = engine_.getEntityTree()->chercher(0);
	if (table)
	{
		std::unique_ptr<VisiteurVerificationQuad> visiteurVerification = std::make_unique <VisiteurVerificationQuad>();

		for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
			NoeudAbstrait* enfant = table->chercher(i);
			if (enfant->estSelectionne())
			{
				// Assigner le nouveau facteur de mise � �chelle.
				PhysicsComponent& physics = enfant->getPhysicsComponent();
				double facteurAvantChangement = physics.scale.x;
				physics.scale.x = facteurMiseAEchelle;

				// V�rifier la nouvelle position du noeud.
				engine_.getEntityTree()->accepterVisiteur(visiteurVerification.get());
				bool positionValide = visiteurVerification->objetsDansZoneSimulation();
				if (!positionValide)
				{
					physics.scale.x = facteurAvantChangement;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerPositionRelativeX(double positionRelativeX)
///
/// Cette fonction assigne une position en X � un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: position en X de l'objet
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerPositionRelativeX(const double& positionRelativeX)
{
	NoeudAbstrait* table = engine_.getEntityTree()->chercher(0);
	if (table)
	{
		std::unique_ptr<VisiteurVerificationQuad> visiteurVerification = std::make_unique <VisiteurVerificationQuad>();
		unsigned int nEnfants = table->obtenirNombreEnfants();
		for (unsigned int i = 0; i < nEnfants; i++) {
			NoeudAbstrait* enfant = table->chercher(i);
			if (enfant->estSelectionne())
			{
				PhysicsComponent& physics = enfant->getPhysicsComponent();

				// Ajuster la position du noeud et garder la derni�re position.
				double positionXAvantChangement = physics.relativePosition.x;
				physics.relativePosition.x = positionRelativeX;

				// Verifier la position du noeud.
				engine_.getEntityTree()->accepterVisiteur(visiteurVerification.get());
				bool positionValide = visiteurVerification->objetsDansZoneSimulation();

				// Replacer le noeud.
				if (!positionValide)
				{
					physics.relativePosition.x = positionXAvantChangement;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerPositionRelativeY(double positionRelativeY)
///
/// Cette fonction assigne une position en Y � un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: position en Y de l'objet
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerPositionRelativeY(const double& positionRelativeY)
{
	NoeudAbstrait* table = engine_.getEntityTree()->chercher(0);
	if (table)
	{
		std::unique_ptr<VisiteurVerificationQuad> visiteurVerification = std::make_unique <VisiteurVerificationQuad>();
		for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
			NoeudAbstrait* enfant = table->chercher(i);
			if (enfant->estSelectionne())
			{
				PhysicsComponent& physics = enfant->getPhysicsComponent();

				// Ajuster la position du noeud et garder la derni�re position.
				double positionYAvantChangement = physics.relativePosition.y;
				physics.relativePosition.y = positionRelativeY;

				// V�rifier que la position est valide.
				engine_.getEntityTree()->accepterVisiteur(visiteurVerification.get());
				bool positionValide = visiteurVerification->objetsDansZoneSimulation();

				// Replacer le noeud.
				if (!positionValide)
				{
					physics.relativePosition.y = positionYAvantChangement;
				}
			}
		}
	}
}