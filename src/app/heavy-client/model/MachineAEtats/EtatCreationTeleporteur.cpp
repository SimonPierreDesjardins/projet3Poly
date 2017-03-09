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
	if (!estClickDrag() && curseurEstSurTable_) {
		// Ajout du teleporteur sur la table.
		glm::dvec3 positionVirtuelle;
		vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
		visiteurCreationTeleporteur_->assignerPositionRelative(positionVirtuelle);
		arbre_->accepterVisiteur(visiteurCreationTeleporteur_.get());
		NoeudAbstrait* teleporteur = visiteurCreationTeleporteur_->obtenirReferenceNoeud();
		
		// Mettre � jour les quads et v�rifier si le nouveau teleporteur se situe � l'ext�rieur de la table.
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
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
