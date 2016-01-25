///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationPoteau.cpp
/// @author Olivier St-Amour
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurCreationPoteau.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include <iostream>

VisiteurCreationPoteau::VisiteurCreationPoteau()
{

}

VisiteurCreationPoteau::VisiteurCreationPoteau(const int& x, const int& y) 
	: VisiteurAbstrait(x, y)
{
}


VisiteurCreationPoteau::~VisiteurCreationPoteau()
{

}

void VisiteurCreationPoteau::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

void VisiteurCreationPoteau::visiter(NoeudTable* noeud)
{
	std::cout << "nouveau poteau à la position: " << positionRelative_[0] << " : " << positionRelative_[1];
	std::cout << " : " <<  positionRelative_[2] << std::endl;
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_POTEAU);
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	noeud->ajouter(nouveauNoeud);
}

void VisiteurCreationPoteau::visiter(NoeudPoteau* noeud)
{

}