///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurDeplacement.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"


/// Constructeur par défaut.
VisiteurDeplacement::VisiteurDeplacement()
{
}

/// Destructeur.
VisiteurDeplacement::~VisiteurDeplacement()
{
}

void VisiteurDeplacement::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

void VisiteurDeplacement::visiter(NoeudTable* noeud)
{
	NoeudAbstrait* enfant;
	glm::dvec3 positionVirtuelle;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne())
		{
			positionVirtuelle = enfant->obtenirPositionRelative();
			enfant->assignerPositionRelative(positionVirtuelle + positionRelative_);
		}
	}
}