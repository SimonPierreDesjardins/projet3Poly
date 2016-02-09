///////////////////////////////////////////////////////////////////////////
/// @file EtatDeplacement.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatDeplacement.h"
#include "VisiteurDeplacement.h"
#include "FacadeModele.h"
#include <iostream>

EtatDeplacement::EtatDeplacement()
{
	visiteur_ = std::make_unique<VisiteurDeplacement>();
	typeEtat_ = DEPLACEMENT;
}

EtatDeplacement::~EtatDeplacement()
{
	if (clicGaucheEnfonce_)
	{
		visiteur_->assignerPositionRelative(positionVirtuelleInitiale_ - dernierePositionVirtuelle_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
	}
}

void EtatDeplacement::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, dernierePositionVirtuelle_);
	positionVirtuelleInitiale_ = dernierePositionVirtuelle_;
}

void EtatDeplacement::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
}

void EtatDeplacement::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	if (clicGaucheEnfonce_)
	{
		visiteur_->assignerPositionRelative(positionVirtuelle - dernierePositionVirtuelle_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
		dernierePositionVirtuelle_ = positionVirtuelle;
	}
}