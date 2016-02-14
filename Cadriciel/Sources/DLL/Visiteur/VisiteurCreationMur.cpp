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

VisiteurCreationMur::VisiteurCreationMur()
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
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_MUR);
	referenceNoeud_ = nouveauNoeud.get();
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	noeud->ajouter(nouveauNoeud);
}

void VisiteurCreationMur::visiter(NoeudPoteau* noeud)
{

}