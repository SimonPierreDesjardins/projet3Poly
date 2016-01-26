///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationMur.cpp
/// @author Frederic Gregoire
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurCreationMur.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include <iostream>

VisiteurCreationMur::VisiteurCreationMur()
{

}

VisiteurCreationMur::VisiteurCreationMur(const int& x, const int& y)
: VisiteurAbstrait(x, y)
{

}

VisiteurCreationMur::~VisiteurCreationMur()
{

}

void VisiteurCreationMur::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

void VisiteurCreationMur::visiter(NoeudTable* noeud)
{
	std::cout << "Debut de mur a la position: " << positionRelative_[0] << " : " << positionRelative_[1];
	std::cout << " : " << positionRelative_[2] << std::endl;

	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_MUR);
	positionRelative_[2] = 0;
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	noeud->ajouter(nouveauNoeud);
	referenceNoeud_ = nouveauNoeud;

}

void VisiteurCreationMur::visiter(NoeudPoteau* noeud)
{

}