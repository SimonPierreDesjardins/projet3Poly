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
#include "VisiteurVerificationObjets.h"
#include "FacadeModele.h"
#include <iostream>

EtatDeplacement::EtatDeplacement()
{
	visiteurDeplacement_ = std::make_unique<VisiteurDeplacement>();
	visiteurVerificationObjets_ = std::make_unique<VisiteurVerificationObjets>();
}

EtatDeplacement::~EtatDeplacement()
{
	if (clicGaucheEnfonce_)
	{
		reinitialiser();
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
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurVerificationObjets_.get());
	if (!visiteurVerificationObjets_->objetsDansZoneSimulation())
	{
		reinitialiser();
	}
}

void EtatDeplacement::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	if (clicGaucheEnfonce_)
	{
		visiteurDeplacement_->assignerPositionRelative(positionVirtuelle - dernierePositionVirtuelle_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurDeplacement_.get());
		dernierePositionVirtuelle_ = positionVirtuelle;
	}
}

void EtatDeplacement::reinitialiser()
{
	visiteurDeplacement_->assignerPositionRelative(positionVirtuelleInitiale_ - dernierePositionVirtuelle_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurDeplacement_.get());
}