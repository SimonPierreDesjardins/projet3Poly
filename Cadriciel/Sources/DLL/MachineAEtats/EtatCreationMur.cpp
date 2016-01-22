///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationMur.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationMur.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

#include <iostream> 

EtatCreationMur::EtatCreationMur()
{
	std::cout << "Creation de poteau" << std::endl;
}

EtatCreationMur::~EtatCreationMur()
{

}

void EtatCreationMur::gererClicGaucheEnfonce(const int& x, const int& y)
{
	std::cout << x << " " << y << std::endl;
}

void EtatCreationMur::gererClicGaucheRelache(const int& x, const int& y)
{
	//std::cout << x << " " << y << std::endl;
	std::unique_ptr<VisiteurCreationMur> visiteur = std::make_unique<VisiteurCreationMur>(x, y);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur.get());
}

void EtatCreationMur::effectuerOperation()
{

}