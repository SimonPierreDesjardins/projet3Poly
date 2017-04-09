///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationPoteau.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationPoteau.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "glm\glm.hpp"

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationPoteau::EtatCreationPoteau()
///
/// Constructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatCreationPoteau::EtatCreationPoteau(client_network::ClientMapSession* mapSession)
	: OnlineTool(mapSession)
{
	setType(CREATION_POTEAU);
	visiteurCreationPoteau_ = std::make_unique<VisiteurCreationPoteau>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationPoteau::~EtatCreationPoteau()
///
/// Destructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatCreationPoteau::~EtatCreationPoteau()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationPoteau::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à true si le bouton gauche de la souris est
/// appuyé et sauvegarde la position courante.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::gererClicGaucheEnfonce(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheEnfonce(x, y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationPoteau::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à false si le bouton gauche de la souris est
/// relâché et crée un poteau sur la table
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::gererClicGaucheRelache(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheRelache(x, y);
	if (!estClickDrag() && curseurEstSurTable_) {
		// Ajout du poteau sur la table.
		glm::dvec3 positionVirtuelle;
		vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
		visiteurCreationPoteau_->assignerPositionRelative(positionVirtuelle);

		arbre_->accepterVisiteur(visiteurCreationPoteau_.get());

		NoeudAbstrait* poteau = visiteurCreationPoteau_->obtenirReferenceNoeud();
		poteau->assignerSelection(false);
		// Mettre à jour les quads et vérifier si le nouveau poteau se situe à l'extérieur de la table.
		arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
		if (visiteurVerificationQuad_->objetsDansZoneSimulation()) 
		{
			// On confirme la création d'objet avec le serveur.
			mapSession_->localEntityCreated(poteau);
			//mapSession_->updateSelectionStateLocalEntity(poteau, false);
		}
		else 
		{
			arbre_->chercher("table")->effacer(poteau);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationPoteau::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction gère les mouvements de la souris. Si le clique droit est enfoncé
/// on peux déplacer la caméra, sinon rien
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	gererPositionCurseur(positionVirtuelle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationMur::gererEstSurTableConcret(const bool& positionEstSurTable)
///
/// Cette fonction affiche l'objet si le curseur est sur la table et arrête
/// d'afficher l'objet si le curseur n'est pas sur la table.
///
/// @param bool positionEstSurTable: True si curseur est sur la table, sinon false.
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::gererPositionCurseurConcret(const bool& positionEstSurTable)
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
/// @fn void EtatAbstrait::assignerSymboleCurseur()
///
/// Cette fonction assigne le symbole interdit au curseur si celui-ci
/// ne se trouve pas sur la table. 
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::assignerSymboleCurseur()
{
	if (!curseurEstSurTable_) {
		HCURSOR Cursor = LoadCursor(NULL, IDC_NO);
		SetCursor(Cursor);
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
