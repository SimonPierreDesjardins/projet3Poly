///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationTeleporteur.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationTeleporteur.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "glm\glm.hpp"
#include "NoeudPaireTeleporteurs.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationTeleporteur::EtatCreationTeleporteur()
///
/// Constructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatCreationTeleporteur::EtatCreationTeleporteur()
{
	setType(CREATION_TELEPORTOR);
	visiteurCreationTeleporteur_ = std::make_unique<VisiteurCreationTeleporteur>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
	paireTeleporteurs_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_PAIRTELEPORT);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationTeleporteur::~EtatCreationTeleporteur()
///
/// Destructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatCreationTeleporteur::~EtatCreationTeleporteur()
{
	if (enCreation_)
	{
		arbre_->chercher("table")->effacer(paireTeleporteurs_.get());
		enCreation_ = false;
		teleporteur_ = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationTeleporteur::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à true si le bouton gauche de la souris est
/// appuyé et sauvegarde la position courante.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationTeleporteur::gererClicGaucheEnfonce(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheEnfonce(x, y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationTeleporteur::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à false si le bouton gauche de la souris est
/// relâché et crée un teleporteur sur la table
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationTeleporteur::gererClicGaucheRelache(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheRelache(x, y);
	glm::dvec3 positionVirtuelle;
	if (!estClickDrag() && curseurEstSurTable_)
	{
		
		//Premier clic
		if (!enCreation_)
		{
			enCreation_ = true;
			vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
			visiteurCreationTeleporteur_->assignerPositionRelative(positionVirtuelle);
			arbre_->accepterVisiteur(visiteurCreationTeleporteur_.get());

			teleporteur_ = visiteurCreationTeleporteur_->obtenirReferenceNoeud();
			arbre_->chercher(0)->ajouter(paireTeleporteurs_);
			paireTeleporteurs_->ajouter(teleporteur_);
			teleporteur_->getPhysicsComponent().absolutePosition = positionVirtuelle;
			teleporteur_->getPhysicsComponent().relativePosition = positionVirtuelle;
			//teleporteur_->assignerTeleporteur(nullptr);//pas a faire ici

			arbre_->accepterVisiteur(visiteurVerificationQuad_.get());

			if (!visiteurVerificationQuad_->objetsDansZoneSimulation()) {
				arbre_->chercher("table")->effacer(paireTeleporteurs_.get()); //a voir sinon remove tp
				teleporteur_ = nullptr;
				enCreation_ = false;
				ancienTeleporteur_ = nullptr;
			}
		}
		//Deuxieme clic
		else
		{
			ancienTeleporteur_ = teleporteur_;
			vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
			visiteurCreationTeleporteur_->assignerPositionRelative(positionVirtuelle);
			arbre_->accepterVisiteur(visiteurCreationTeleporteur_.get());
			teleporteur_ = visiteurCreationTeleporteur_->obtenirReferenceNoeud();
			paireTeleporteurs_->ajouter(teleporteur_);
			teleporteur_->getPhysicsComponent().absolutePosition = positionVirtuelle;
			teleporteur_->getPhysicsComponent().relativePosition = positionVirtuelle;
			arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
			//ancienTeleporteur_->assignerTeleporteur(teleporteur_);
			//teleporteur_->assignerTeleporteur(ancienTeleporteur_); a faire dans le ajouter

			if (!visiteurVerificationQuad_->objetsDansZoneSimulation()) {
				arbre_->chercher("table")->effacer(teleporteur_.get());
				teleporteur_ = ancienTeleporteur_;
				enCreation_ = true;
				ancienTeleporteur_ = nullptr;
			}
			else
			{
				enCreation_ = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationTeleporteur::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction gère les mouvements de la souris. Si le clique droit est enfoncé
/// on peux déplacer la caméra, sinon rien
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationTeleporteur::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	gererPositionCurseur(positionVirtuelle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationTeleporteur::gererEstSurTableConcret(const bool& positionEstSurTable)
///
/// Cette fonction affiche l'objet si le curseur est sur la table et arrête
/// d'afficher l'objet si le curseur n'est pas sur la table.
///
/// @param bool positionEstSurTable: True si curseur est sur la table, sinon false.
///
////////////////////////////////////////////////////////////////////////
void EtatCreationTeleporteur::gererPositionCurseurConcret(const bool& positionEstSurTable)
{
	if (positionEstSurTable && !curseurEstSurTable_) {
		curseurEstSurTable_ = true;
	}
	else if (!positionEstSurTable && curseurEstSurTable_) {
		curseurEstSurTable_ = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationTeleporteur::assignerSymboleCurseur()
///
/// Cette fonction assigne le symbole interdit au curseur si celui-ci
/// ne se trouve pas sur la table. 
///
////////////////////////////////////////////////////////////////////////
void EtatCreationTeleporteur::assignerSymboleCurseur()
{
	if (!curseurEstSurTable_) {
		HCURSOR Cursor = LoadCursor(NULL, IDC_NO);
		SetCursor(Cursor);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationTeleporteur::gererToucheEchappe()
///
/// Cette fonction supprime le teleporteur si le 2e n'est pas fait.
///
////////////////////////////////////////////////////////////////////////
void EtatCreationTeleporteur::gererToucheEchappe()
{
	if (enCreation_)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(paireTeleporteurs_.get());
		enCreation_ = false;
		teleporteur_ = nullptr;
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
