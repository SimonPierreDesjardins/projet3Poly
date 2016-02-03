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
#include "VisiteurDuplication.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

EtatDuplication::EtatDuplication()
{
	visiteur_ = std::make_unique<VisiteurDuplication>();
}

EtatDuplication::~EtatDuplication()
{
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
	
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	if (!enDuplication_)
	{
		enDuplication_ = true;
		arbre->accepterVisiteur(visiteur_.get());
		duplication_ = visiteur_->obtenirReferenceNoeud();
	}
	else
	{
		enDuplication_ = false;
		duplication_->accepterVisiteur(visiteur_.get());
	}
}

void EtatDuplication::gererToucheEchappe()
{
	if (enDuplication_)
	{
		enDuplication_ = false;
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->effacer(duplication_);
		duplication_ = nullptr;
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