///////////////////////////////////////////////////////////////////////////
/// @file EtatDuplication.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatDuplication.h"
#include "VisiteurTypes.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatDuplication::EtatDuplication()
///
/// Constructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatDuplication::EtatDuplication(client_network::MapSession* mapSession)
	: OnlineTool(mapSession), 
	  visiteurDeplacement_(mapSession),
	  visiteurDuplication_(mapSession),
	  visiteurSuppression_(mapSession)
{
	setType(DUPLICATION);
	arbre_->accepterVisiteur(&visiteurDuplication_);
	duplication_ = visiteurDuplication_.obtenirDuplication();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatDuplication::~EtatDuplication()
///
/// Destructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatDuplication::~EtatDuplication()
{
	if (duplication_)
	{
		duplication_->accepterVisiteur(&visiteurSuppression_);
	}
	duplication_ = nullptr;
	arbre_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationMur::gererPositionCurseurConcret(const bool& positionEstSurTable)
///
/// Cette fonction affiche l'objet si le curseur est sur la table et arrête
/// d'afficher l'objet si le curseur n'est pas sur la table.
///
/// @param bool positionEstSurTable: True si curseur est sur la table, sinon false.
///
////////////////////////////////////////////////////////////////////////
void EtatDuplication::gererPositionCurseurConcret(const bool& positionEstSurTable)
{
	if (positionEstSurTable && !curseurEstSurTable_) {
		curseurEstSurTable_ = true;
		if (duplication_ != nullptr) {
			duplication_->assignerAffiche(true);
		}
	}
	else if (!positionEstSurTable && curseurEstSurTable_) {
		curseurEstSurTable_ = false;
		if (duplication_ != nullptr) {
			duplication_->assignerAffiche(false);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDuplication::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction duplique les objets sélectionnés. Si on objet est à l'extérieur
/// on les remets à la position initiale. Si le curseur n'est pas sur la table on
/// ne fait rien.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatDuplication::gererClicGaucheRelache(const int& x, const int& y)
{
	// Si le curseur n'est pas sur la table, on ne gere par le clic gauche.
	if (curseurEstSurTable_ && !estClickDrag()) {
		if (arbre_ != nullptr) {
			arbre_->accepterVisiteur(&visiteurVerificationQuad_);
		}
		bool objetsDansZoneSimulation =	visiteurVerificationQuad_.objetsDansZoneSimulation();
		// Ajouter la duplication sur la table.
		if (objetsDansZoneSimulation) {
			visiteurDuplication_.copyDuplicatedObjects(duplication_);
			duplication_->accepterVisiteur(&visiteurDuplication_);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDuplication::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction assigne la position en x et y courante à la duplication.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatDuplication::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionRelative;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionRelative);
	
	gererPositionCurseur(positionRelative);

	visiteurDeplacement_.assignerPositionRelative(positionRelative);
	duplication_->accepterVisiteur(&visiteurDeplacement_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::assignerSymboleCurseur()
///
/// Cette fonction assigne le symbole interdit au curseur si celui-ci
/// ne se trouve pas sur la table. 
///
////////////////////////////////////////////////////////////////////////
void EtatDuplication::assignerSymboleCurseur()
{
	if (!curseurEstSurTable_) {
		HCURSOR Cursor = LoadCursor(NULL, IDC_NO);
		SetCursor(Cursor);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
