///////////////////////////////////////////////////////////////////////////
/// @file EtatDupliquation.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatDupliquation.h"
#include "VisiteurTypes.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

EtatDupliquation::EtatDupliquation()
{
	typeEtat_ = DUPLICATION;
	visiteurDupliquation_ = std::make_unique<VisiteurDupliquation>();
	visiteurMiseAJourQuad_ = std::make_unique<VisiteurMiseAJourQuad>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

EtatDupliquation::~EtatDupliquation()
{
	reinitialiser();
	arbre_ = nullptr;
}

void EtatDupliquation::gererEstSurTableConcret(bool positionEstSurTable)
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

void EtatDupliquation::gererClicGaucheRelache(const int& x, const int& y)
{
	// Si le curseur n'est pas sur la table, on ne gere par le clic gauche.
	if (!curseurEstSurTable_) return;
	
	if (arbre_ != nullptr)
	{
		arbre_->accepterVisiteur(visiteurMiseAJourQuad_.get());
		arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
	}

	bool objetsDansZoneSimulation =	visiteurVerificationQuad_->objetsDansZoneSimulation();
	// On commence une duplication si on ne se trouve pas en duplication.
	if (!enDuplication_)
	{
		enDuplication_ = true;
		arbre_->accepterVisiteur(visiteurDupliquation_.get());
		duplication_ = visiteurDupliquation_->obtenirDuplication();
	}

	// Réinitialiser la duplication si un des objets ne se trouve pas sur la table.
	else if (enDuplication_ && !objetsDansZoneSimulation)
	{
		reinitialiser();
	}

	// Ajouter la duplication sur la table autrement.
	else if (enDuplication_ && objetsDansZoneSimulation)
	{
		enDuplication_ = false;
		duplication_->accepterVisiteur(visiteurDupliquation_.get());
	}
}

void EtatDupliquation::gererToucheEchappe()
{
	if (enDuplication_)
	{
		reinitialiser();
	}
}

void EtatDupliquation::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	gererEstSurTable(positionVirtuelle);

	if (enDuplication_)
	{
		duplication_->assignerPositionRelative(positionVirtuelle);
	}
}


void EtatDupliquation::reinitialiser()
{
	enDuplication_ = false;
	if (duplication_ != nullptr && arbre_ != nullptr)
	{
		arbre_->chercher("table")->effacer(duplication_);
	}
	duplication_ = nullptr;
}