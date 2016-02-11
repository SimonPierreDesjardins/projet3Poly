///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.cpp
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurSuppression.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "Modele3D.h"
#include <iostream>

VisiteurSuppression::VisiteurSuppression()
{

}

VisiteurSuppression::~VisiteurSuppression()
{

}

void VisiteurSuppression::visiter(NoeudTable* noeud)
{
	for (unsigned i = noeud->obtenirNombreEnfants(); i > 0; i--)
	{
		if (noeud->chercher(i-1)->estSelectionne())
		{
			noeud->effacer(noeud->chercher(i-1));
		}
	}
}