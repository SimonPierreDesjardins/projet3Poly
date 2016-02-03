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
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		modele::Modele3D const* modeleEnfant = noeud->chercher(i)->getModele();
		utilitaire::BoiteEnglobante boite = utilitaire::calculerBoiteEnglobante(*modeleEnfant);
		/*
		float boiteMinX = boite.coinMin[0], boiteMinY = boite.coinMin[1], boiteMinZ = boite.coinMin[2], boiteMaxX = boite.coinMax[0], boiteMaxY = boite.coinMax[1], boiteMaxZ = boite.coinMax[2];

		glm::dvec3 origine, pointLigne;
		origine[0] = 0.0;
		origine[1] = 0.0;
		origine[2] = 0.0;

		pointLigne[0] = noeud->chercher(i)->obtenirPositionRelative()[0];
		pointLigne[1] = noeud->chercher(i)->obtenirPositionRelative()[1];
		pointLigne[2] = noeud->chercher(i)->obtenirPositionRelative()[2];

		double r;
		r = utilitaire::calculerDistanceHypothenuse(origine, pointLigne);

		double angleRotation = noeud->chercher(i)->obtenirAngleRotation();

		boiteMinX = r*cos(angleRotation);
		boiteMinY = r*sin(angleRotation);

		boiteMaxX = 

		boite.coinMin[0] *= noeud->chercher(i)->obtenirFacteurDimension();
		boite.coinMin[1] *= noeud->chercher(i)->obtenirFacteurDimension();
		boite.coinMin[2] *= noeud->chercher(i)->obtenirFacteurDimension();

		boite.coinMax[0] *= noeud->chercher(i)->obtenirFacteurDimension();
		boite.coinMax[1] *= noeud->chercher(i)->obtenirFacteurDimension();
		boite.coinMax[2] *= noeud->chercher(i)->obtenirFacteurDimension();
		*/

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