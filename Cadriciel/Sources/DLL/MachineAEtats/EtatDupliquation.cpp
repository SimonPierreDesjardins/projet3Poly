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

EtatDuplication::EtatDuplication()
{
	typeEtat_ = DUPLICATION;
	visiteurDuplication_ = std::make_unique<VisiteurDuplication>();
	visiteurVerificationObjets_ = std::make_unique<VisiteurVerificationQuad>();
}

EtatDuplication::~EtatDuplication()
{
	reinitialiser();
	arbre_ = nullptr;
}

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

void EtatDuplication::gererClicGaucheRelache(const int& x, const int& y)
{
	// Si le curseur n'est pas sur la table, on ne gere par le clic gauche.
	if (!curseurEstSurTable_) return;

	// Obtenir l'arbre et vérifier si les objets sont sur la table.
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	arbre->accepterVisiteur(visiteurVerificationObjets_.get());
	bool objetsDansZoneSimulation =	visiteurVerificationObjets_->objetsDansZoneSimulation();
	
	// On commence une duplication si on ne se trouve pas en duplication.
	if (!enDuplication_)
	{
		enDuplication_ = true;
		arbre->accepterVisiteur(visiteurDuplication_.get());
		duplication_ = visiteurDuplication_->obtenirDuplication();
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
		duplication_->accepterVisiteur(visiteurDuplication_.get());
	}
}

void EtatDuplication::gererToucheEchappe()
{
	if (enDuplication_)
	{
		reinitialiser();
	}
}

void EtatDuplication::gererMouvementSouris(const int& x, const int& y)
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


void EtatDuplication::reinitialiser()
{
	enDuplication_ = false;
	if (duplication_ != nullptr && arbre_ != nullptr)
	{
		arbre_->chercher("table")->effacer(duplication_);
	}
	duplication_ = nullptr;
}