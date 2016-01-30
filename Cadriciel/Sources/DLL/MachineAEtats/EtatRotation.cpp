///////////////////////////////////////////////////////////////////////////
/// @file EtatRotation.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatRotation.h"
#include "VisiteurRotation.h"
#include "ArbreRenduINF2990.h"
#include <iostream>


EtatRotation::EtatRotation()
{
	std::cout << "Outil de rotation" << std::endl;
	visiteur_ = std::make_unique<VisiteurRotation>();
}

EtatRotation::~EtatRotation()
{

}

void EtatRotation::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	dernierePositionY_ = y;
}

void EtatRotation::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
}


void EtatRotation::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	if (clicGaucheEnfonce_)
	{
		std::cout << "angle:" << y - dernierePositionY_ << std::endl;
		visiteur_->assignerAngleRotation((double)y - dernierePositionY_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
		dernierePositionY_ = y;
	}

}