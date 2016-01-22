///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationLigneNoire.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationLigneNoire.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

#include <iostream> 

EtatCreationLigneNoire::EtatCreationLigneNoire()
{
	std::cout << "Creation de poteau" << std::endl;
}

EtatCreationLigneNoire::~EtatCreationLigneNoire()
{

}

void EtatCreationLigneNoire::gererClicGaucheEnfonce(const int& x, const int& y)
{
	std::cout << x << " " << y << std::endl;
}

void EtatCreationLigneNoire::gererClicGaucheRelache(const int& x, const int& y)
{
	//std::cout << x << " " << y << std::endl;
	std::unique_ptr<VisiteurCreationLigne> visiteur = std::make_unique<VisiteurCreationLigne>(x, y);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur.get());
}

void EtatCreationLigneNoire::effectuerOperation()
{

}