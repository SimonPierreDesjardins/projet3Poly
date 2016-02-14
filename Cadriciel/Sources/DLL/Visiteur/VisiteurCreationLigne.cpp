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

VisiteurCreationLigne::VisiteurCreationLigne()
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
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	noeud->ajouter(nouveauNoeud);
	referenceNoeud_ = nouveauNoeud.get();
}