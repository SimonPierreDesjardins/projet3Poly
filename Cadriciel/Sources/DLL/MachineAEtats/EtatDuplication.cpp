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
/// Constructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatDuplication::EtatDuplication()
{
	typeEtat_ = DUPLICATION;
	visiteurDuplication_ = std::make_unique<VisiteurDuplication>();
	visiteurMiseAJourQuad_ = std::make_unique<VisiteurMiseAJourQuad>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();

	// On commence une duplication si on ne se trouve pas en duplication.

	arbre_->accepterVisiteur(visiteurDuplication_.get());
	duplication_ = visiteurDuplication_->obtenirDuplication();
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(currentPosition_.x, currentPosition_.y, positionVirtuelle);
	duplication_->assignerPositionRelative(positionVirtuelle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatDuplication::~EtatDuplication()
///
/// Destructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatDuplication::~EtatDuplication()
{
	if (duplication_ != nullptr && arbre_ != nullptr)
	{
		arbre_->chercher("table")->effacer(duplication_);
	}
	duplication_ = nullptr;
	arbre_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDuplication::gererEstSurTableConcret(bool positionEstSurTable)
///
/// Cette fonction affiche l'objet si le curseur est sur la table et arr�te
/// d'afficher l'objet si le curseur n'est pas sur la table.
///
/// @param bool positionEstSurTable: True si curseur est sur la table, sinon false.
///
////////////////////////////////////////////////////////////////////////
void EtatDuplication::gererEstSurTableConcret(bool positionEstSurTable)
{
	assignerSymbolePointeur(positionEstSurTable);

	if (positionEstSurTable && !curseurEstSurTable_)
	{
		curseurEstSurTable_ = true;
		if (duplication_ != nullptr)
		{
			duplication_->assignerAffiche(true);
		}
	}
	else if (!positionEstSurTable && curseurEstSurTable_)
	{
		curseurEstSurTable_ = false;
		if (duplication_ != nullptr)
		{
			duplication_->assignerAffiche(false);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDuplication::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction duplique les objets s�lectionn�s. Si on objet est � l'ext�rieur
/// on les remets � la position initiale. Si le curseur n'est pas sur la table on
/// ne fait rien.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatDuplication::gererClicGaucheRelache(const int& x, const int& y)
{
	// Si le curseur n'est pas sur la table, on ne gere par le clic gauche.
	if (!curseurEstSurTable_) return;
	
	if (arbre_ != nullptr)
	{
		arbre_->accepterVisiteur(visiteurMiseAJourQuad_.get());
		arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
	}

	bool objetsDansZoneSimulation =	visiteurVerificationQuad_->objetsDansZoneSimulation();

	// Ajouter la duplication sur la table.
	if (objetsDansZoneSimulation)
	{
		duplication_->accepterVisiteur(visiteurDuplication_.get());
		duplication_ = visiteurDuplication_->obtenirDuplication();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDuplication::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction assigne la position en x et y au nouveau objet si une duplication
/// est en cours.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatDuplication::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	gererEstSurTable(positionVirtuelle);

	duplication_->assignerPositionRelative(positionVirtuelle);

}