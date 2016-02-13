///////////////////////////////////////////////////////////////////////////
/// @file EtatRotation.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "EtatRotation.h"
#include "VisiteurRotation.h"
#include "ArbreRenduINF2990.h"
#include <iostream>


EtatRotation::EtatRotation()
{
	typeEtat_ = ROTATION;
	visiteurRotation_ = std::make_unique<VisiteurRotation>();
	visiteurMiseAJourQuad_ = std::make_unique<VisiteurMiseAJourQuad>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

EtatRotation::~EtatRotation()
{
	if (clicGaucheEnfonce_)
	{
		reinitialiser();
	}
}

void EtatRotation::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	dernierePositionY_ = y;
	positionInitialeY_ = y;
}

void EtatRotation::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
	if (arbre_ != nullptr)
	{
		arbre_->accepterVisiteur(visiteurMiseAJourQuad_.get());
		arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
	}
	if (!visiteurVerificationQuad_->objetsDansZoneSimulation())
	{
		reinitialiser();
	}
}


void EtatRotation::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	if (clicGaucheEnfonce_)
	{
		visiteurRotation_->assignerAngleRotation((double)(y - dernierePositionY_));
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurRotation_.get());
		dernierePositionY_ = y;
	}
}

void EtatRotation::reinitialiser()
{
	visiteurRotation_->assignerAngleRotation((double)(positionInitialeY_- dernierePositionY_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurRotation_.get());
}
