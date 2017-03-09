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
/// Constructeur par défault
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
/// Destructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatCreationTeleporteur::~EtatCreationTeleporteur()
{

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
	if (!estClickDrag() && curseurEstSurTable_) {
		// Ajout du teleporteur sur la table.
		glm::dvec3 positionVirtuelle;
		vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
		visiteurCreationTeleporteur_->assignerPositionRelative(positionVirtuelle);
		arbre_->accepterVisiteur(visiteurCreationTeleporteur_.get());
		NoeudAbstrait* teleporteur = visiteurCreationTeleporteur_->obtenirReferenceNoeud();
		
		// Mettre à jour les quads et vérifier si le nouveau teleporteur se situe à l'extérieur de la table.
		arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
		if (!visiteurVerificationQuad_->objetsDansZoneSimulation()) {
			arbre_->chercher("table")->effacer(teleporteur);
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
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
