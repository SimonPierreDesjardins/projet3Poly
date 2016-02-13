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
#include "VisiteurTypes.h"
#include "FacadeModele.h"
#include <iostream>

EtatMiseAEchelle::EtatMiseAEchelle()
{
	typeEtat_ = MISE_A_ECHELLE;
	visiteurMiseAEchelle_ = std::make_unique<VisiteurMiseAEchelle>();
	visiteurMiseAJourQuad_ = std::make_unique<VisiteurMiseAJourQuad>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

EtatMiseAEchelle::~EtatMiseAEchelle()
{
	if (clicGaucheEnfonce_)
	{
		reinitialiser();
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

void EtatMiseAEchelle::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	if (clicGaucheEnfonce_)
	{
		visiteurMiseAEchelle_->assignerFacteurMiseAEchelle((double)(dernierePositionY_ - y));
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAEchelle_.get());
		dernierePositionY_ = y;
	}
}

void EtatMiseAEchelle::reinitialiser()
{
	visiteurMiseAEchelle_->assignerFacteurMiseAEchelle((double)(dernierePositionY_ - positionInitialeY_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAEchelle_.get());
}
