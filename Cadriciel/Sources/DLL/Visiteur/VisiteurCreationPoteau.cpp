#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
#include "VisiteurCreationPoteau.h"
#include "ArbreRenduINF2990.h"
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

}

void VisiteurCreationPoteau::visiter(NoeudPoteau* noeud)
{

}