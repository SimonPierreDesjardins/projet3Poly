////////////////////////////////////////////////
/// @file   VisiteurAbstrait.cpp
/// @author Olivier St-Amour
/// @date   20016-01-13
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::VisiteurAbstrait()
///
/// Constructeur par défaut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAbstrait::VisiteurAbstrait()
{
}

VisiteurAbstrait::VisiteurAbstrait(const int& x, const int& y)
{
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelleClic_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::~VisiteurAbstrait()
///
/// Destructeur déclaré virtuel pour les classes dérivées.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAbstrait::~VisiteurAbstrait()
{

}

void VisiteurAbstrait::visiter(ArbreRendu* noeud)
{

}

void VisiteurAbstrait::visiter(NoeudTable* noeud)
{

}
void VisiteurAbstrait::visiter(NoeudPoteau* noeud)
{

}

void VisiteurAbstrait::visiter(NoeudMur* noeud)
{

}

void VisiteurAbstrait::visiter(NoeudLigneNoire* noeud)
{

}