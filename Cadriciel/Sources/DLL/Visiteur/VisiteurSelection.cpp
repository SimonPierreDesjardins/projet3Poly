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

VisiteurSelection::~VisiteurSelection()
{

}

void VisiteurSelection::visiter(ArbreRendu* noeud)
{
	noeud->mettreAJourQuadEnglobant();
	noeud->chercher("table")->accepterVisiteur(this);
}


void VisiteurSelection::visiter(NoeudTable* noeud)
{
	if (!estDrag_)
	{
		if (!ctrlAppuye_)
		{
			noeud->deselectionnerTout();
		}
		NoeudAbstrait* enfant;
		for (unsigned i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			
			enfant = noeud->chercher(i);
			enfant->accepterVisiteur(this);
		}
	}
	else
	{
		if (!ctrlAppuye_)
		{
			noeud->deselectionnerTout();
		}
		for (unsigned i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{

		}
	}
}

void VisiteurSelection::visiterRectangle(NoeudTable* noeud)
{
	std::cout << "Selection par Rectangle Elastique de :" << positionRelativeAvant_[0] << ", " << positionRelativeAvant_[1] << " a " << positionRelativeApres_[0] << ", " << positionRelativeApres_[1] << std::endl;
}

void VisiteurSelection::assignerControl(bool estControl)
{
	ctrlAppuye_ = estControl;
}

bool VisiteurSelection::estDansRectangleElastique(glm::dvec3 coinRectElastMin, glm::dvec3 coinRectElastMax, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, glm::dvec3 p4)
{
	glm::dvec3 rectElast1, rectElast2, rectElast3, rectElast4, points[4] = { p1, p2, p3, p4 };
	if (coinRectElastMax[0] < coinRectElastMin[0])
	{
		rectElast1[0] = coinRectElastMax[0];
		rectElast2[0] = coinRectElastMin[0];
		rectElast3[0] = coinRectElastMax[0];
		rectElast4[0] = coinRectElastMin[0];
	}
	else
	{
		rectElast1[0] = coinRectElastMin[0];
		rectElast2[0] = coinRectElastMax[0];
		rectElast3[0] = coinRectElastMin[0];
		rectElast4[0] = coinRectElastMax[0];
	}

	if (coinRectElastMax[1] < coinRectElastMin[1])
	{
		rectElast1[1] = coinRectElastMax[1];
		rectElast2[1] = coinRectElastMax[1];
		rectElast3[1] = coinRectElastMin[1];
		rectElast4[1] = coinRectElastMin[1];
	}
	else
	{
		rectElast1[1] = coinRectElastMin[1];
		rectElast2[1] = coinRectElastMin[1];
		rectElast3[1] = coinRectElastMax[1];
		rectElast4[1] = coinRectElastMax[1];
	}
	rectElast1[2] = 0;
	rectElast2[2] = 0;
	rectElast3[2] = 0;
	rectElast4[2] = 0;

	bool estDansBoite = true;

	for (unsigned i = 0; i < 4; i++)
	{
		if (points[i][0] < rectElast1[0] || points[i][0] > rectElast2[0] || points[i][1] < rectElast1[1] || points[i][1] > rectElast3[1])
		{
			estDansBoite = false;
		}
	}

	return estDansBoite;
}

void VisiteurSelection::visiter(NoeudPoteau* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobant();
	

	if (utilitaire::calculerPointEstDansQuad(positionRelative_, noeud->obtenirQuadEnglobant()))
	{
		if (ctrlAppuye_)
		{
			noeud->inverserSelection();
		}
		else
		{
			noeud->assignerSelection(true);
		}
	}
}

void VisiteurSelection::visiter(NoeudMur* noeud)
{	

	if (utilitaire::calculerPointEstDansQuad(positionRelative_, noeud->obtenirQuadEnglobant()))
	{
		if (ctrlAppuye_)
		{
			noeud->inverserSelection();
		}
		else 
		{
			noeud->assignerSelection(true);
		}
	}
}

void VisiteurSelection::visiter(NoeudLigne* noeud)
{
	
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
	if (noeud->selectionExiste())
	{
		noeud->selectionnerTout();
	}
}

void VisiteurSelection::visiter(NoeudDepart* noeud)
{

}

void VisiteurSelection::visiter(NoeudSegment* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobant();

	if (utilitaire::calculerPointEstDansQuad(positionRelative_, quad))
	{
		if (ctrlAppuye_)
		{
			noeud->inverserSelection();
		}
		else
		{
			noeud->assignerSelection(true);
		}
	}
}
