///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationLigne.cpp
/// @author Frederic Gregoire
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurCreationLigne.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include <iostream>

VisiteurCreationLigne::VisiteurCreationLigne()
{

}

VisiteurCreationLigne::VisiteurCreationLigne(const int& x, const int& y)
: VisiteurAbstrait(x, y)
{
}


VisiteurCreationLigne::~VisiteurCreationLigne()
{

}

void VisiteurCreationLigne::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

void VisiteurCreationLigne::visiter(NoeudTable* noeud)
{
	std::cout << "nouvelle ligne à la position: " << positionRelative_[0] << " : " << positionRelative_[1];
	std::cout << " : " << positionRelative_[2] << std::endl;
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	nouveauNoeud->assignerSelection(true);
	noeud->ajouter(nouveauNoeud);
	referenceNoeud_ = nouveauNoeud.get();
}