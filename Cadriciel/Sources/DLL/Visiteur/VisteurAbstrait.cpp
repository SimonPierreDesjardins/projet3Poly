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
#include "Modele3D.h"

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

void VisiteurAbstrait::visiterRectangle(NoeudTable* noeud)
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

void VisiteurAbstrait::visiter(NoeudDuplication* noeud)
{

}

void VisiteurAbstrait::visiter(NoeudSegment* noeud)
{

}

void VisiteurAbstrait::visiter(NoeudDepart* noeud)
{

}

void VisiteurAbstrait::visiter(NoeudJonction* noeud)
{

}