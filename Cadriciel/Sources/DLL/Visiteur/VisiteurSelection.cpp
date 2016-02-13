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

void VisiteurSelection::assignerControl(bool ctrlAppuye)
{
	ctrlAppuye_ = ctrlAppuye;
}

void VisiteurSelection::visiter(NoeudPoteau* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobant();

	if (estDrag_ && quadEstDansRectangleElastique(quad) ||
	  (!estDrag_ && utilitaire::calculerPointEstDansQuad(positionRelative_, quad)))
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
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobant();

	if (estDrag_ && quadEstDansRectangleElastique(quad) ||
	  (!estDrag_ && utilitaire::calculerPointEstDansQuad(positionRelative_, quad)))
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
	
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
	if (noeud->estSelectionne())
	{
		noeud->selectionnerTout();
	}
	else
	{
		noeud->deselectionnerTout();
	}
}

void VisiteurSelection::visiter(NoeudDepart* noeud)
{

}

void VisiteurSelection::visiter(NoeudSegment* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobant();
	NoeudAbstrait* pere = noeud->obtenirParent();
	if (estDrag_ && quadEstDansRectangleElastique(quad) ||
	  (!estDrag_ && utilitaire::calculerPointEstDansQuad(positionRelative_, quad)))
	{
		if (ctrlAppuye_)
		{
			pere->inverserSelection();
		}
		else
		{
			pere->assignerSelection(true);
		}
	}
}

void VisiteurSelection::visiter(NoeudJonction* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobant();
	NoeudAbstrait* pere = noeud->obtenirParent();
	if (estDrag_ && quadEstDansRectangleElastique(quad) ||
	  (!estDrag_ && utilitaire::calculerPointEstDansQuad(positionRelative_, quad)))
	{
		if (ctrlAppuye_)
		{
			pere->inverserSelection();
		}
		else
		{
			pere->assignerSelection(true);
		}
	}
}

bool VisiteurSelection::quadEstDansRectangleElastique(const utilitaire::QuadEnglobant& quad)
{
	for (int i = 0; i < 4; i++)
	{
		if (!utilitaire::DANS_LIMITESXY(quad.coins[i].x, xMinRectangleElastique_, xMaxRectangleElastique_,
									   quad.coins[i].y, yMinRectangleElastique_, yMaxRectangleElastique_))
		{
			return false;
		}
	}
	return true;
}