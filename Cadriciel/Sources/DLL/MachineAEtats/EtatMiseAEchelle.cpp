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
#include <iostream>

EtatMiseAEchelle::EtatMiseAEchelle()
{
	visiteur_ = std::make_unique<VisiteurMiseAEchelle>();
}

EtatMiseAEchelle::~EtatMiseAEchelle()
{

}

void EtatMiseAEchelle::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	dernierePositionY_ = y;
}

void EtatMiseAEchelle::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
}

void EtatMiseAEchelle::gererMouvementSouris(const int& x, const int& y)
{

}