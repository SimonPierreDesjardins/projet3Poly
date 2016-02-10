///////////////////////////////////////////////////////////////////////////
/// @file EtatMiseAEchelle.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatMiseAEchelle.h"
#include "VisiteurMiseAEchelle.h"
#include "FacadeModele.h"
#include <iostream>

EtatMiseAEchelle::EtatMiseAEchelle()
{
	visiteur_ = std::make_unique<VisiteurMiseAEchelle>();
}

EtatMiseAEchelle::~EtatMiseAEchelle()
{
	if (clicGaucheEnfonce_)
	{
		visiteur_->assignerFacteurMiseAEchelle((double)(dernierePositionY_ - positionInitialeY_));
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
	}
}

void EtatMiseAEchelle::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	dernierePositionY_ = y;
	positionInitialeY_ = y;
}

void EtatMiseAEchelle::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
}

void EtatMiseAEchelle::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	if (clicGaucheEnfonce_)
	{
		visiteur_->assignerFacteurMiseAEchelle((double)(dernierePositionY_ - y));
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
		dernierePositionY_ = y;
	}
}
