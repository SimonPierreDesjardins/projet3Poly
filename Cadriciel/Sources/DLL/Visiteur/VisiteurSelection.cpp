///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurSelection.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "Modele3D.h"
#include <iostream>

VisiteurSelection::VisiteurSelection()
{

}

VisiteurSelection::VisiteurSelection(const int& x, const int& y)
	: VisiteurAbstrait(x, y)
{
}


VisiteurSelection::~VisiteurSelection()
{

}

void VisiteurSelection::visiter(NoeudTable* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		modele::Modele3D const* modeleEnfant = noeud->chercher(i)->getModele();
		utilitaire::BoiteEnglobante boite = utilitaire::calculerBoiteEnglobante(*modeleEnfant);

		if (positionRelative_[0] < boite.coinMin[0] + noeud->chercher(i)->obtenirPositionRelative()[0] || positionRelative_[0] > boite.coinMax[0] + noeud->chercher(i)->obtenirPositionRelative()[0] || positionRelative_[1] < boite.coinMin[1] + noeud->chercher(i)->obtenirPositionRelative()[1] || positionRelative_[1] > boite.coinMax[1] + noeud->chercher(i)->obtenirPositionRelative()[1])
		{
			noeud->chercher(i)->assignerSelection(0);
		}
		else
		{
			noeud->chercher(i)->assignerSelection(1);
			std::cout << "Lobjet est selectionne" << std::endl;
		}
	}
}