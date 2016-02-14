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
#include <cmath>
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
		visiteurMiseAEchelle_->reinitialiser(arbre_);
	}
}

void EtatMiseAEchelle::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
	vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	dernierePositionY_ = positionVirtuelle.y;
	positionInitialeY_ = positionVirtuelle.y;
	visiteurMiseAEchelle_->initialiser(arbre_);
}

void EtatMiseAEchelle::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
	glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
	vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	dernierePositionY_ = positionVirtuelle.y;

	if (arbre_ != nullptr)
	{
		arbre_->accepterVisiteur(visiteurMiseAJourQuad_.get());
		arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
	}
	if (!visiteurVerificationQuad_->objetsDansZoneSimulation())
	{
		visiteurMiseAEchelle_->reinitialiser(arbre_);
	}
}

void EtatMiseAEchelle::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);

	if (clicGaucheEnfonce_)
	{
		glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
		vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);

		visiteurMiseAEchelle_->assignerFacteurMiseAEchelle(positionVirtuelle.y - dernierePositionY_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAEchelle_.get());

		dernierePositionY_ = positionVirtuelle.y;
	}
}

void EtatMiseAEchelle::reinitialiser()
{
	visiteurMiseAEchelle_->assignerFacteurMiseAEchelle(positionInitialeY_ - dernierePositionY_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAEchelle_.get());
}
