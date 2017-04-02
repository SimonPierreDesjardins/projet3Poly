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

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationTeleporteur::EtatCreationTeleporteur()
///
/// Constructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatCreationTeleporteur::EtatCreationTeleporteur()
{
	visiteurCreationTeleporteur_ = std::make_unique<VisiteurCreationTeleporteur>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationTeleporteur::~EtatCreationTeleporteur()
///
/// Destructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatCreationTeleporteur::~EtatCreationTeleporteur()
{
	if (enCreation_)
	{
		arbre_->chercher("table")->effacer(teleporteur_);
		enCreation_ = false;
		teleporteur_ = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationTeleporteur::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un bool�an � true si le bouton gauche de la souris est
/// appuy� et sauvegarde la position courante.
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
/// Cette fonction assigne un bool�an � false si le bouton gauche de la souris est
/// rel�ch� et cr�e un teleporteur sur la table
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
			teleporteur_->getPhysicsComponent().absolutePosition = positionVirtuelle;
			teleporteur_->assignerTeleporteur(nullptr);

			arbre_->accepterVisiteur(visiteurVerificationQuad_.get());

			if (!visiteurVerificationQuad_->objetsDansZoneSimulation()) {
				arbre_->chercher("table")->effacer(teleporteur_);
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
			teleporteur_->getPhysicsComponent().absolutePosition = positionVirtuelle;
			arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
			ancienTeleporteur_->assignerTeleporteur(teleporteur_);
			teleporteur_->assignerTeleporteur(ancienTeleporteur_);

			if (!visiteurVerificationQuad_->objetsDansZoneSimulation()) {
				arbre_->chercher("table")->effacer(teleporteur_);
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
/// Cette fonction g�re les mouvements de la souris. Si le clique droit est enfonc�
/// on peux d�placer la cam�ra, sinon rien
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
/// Cette fonction affiche l'objet si le curseur est sur la table et arr�te
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
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(teleporteur_);
		enCreation_ = false;
		teleporteur_ = nullptr;
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
