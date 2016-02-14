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

VisiteurCreationPoteau::VisiteurCreationPoteau()
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
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_POTEAU);
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	noeud->ajouter(nouveauNoeud);
	referenceNoeud_ = nouveauNoeud.get();
}