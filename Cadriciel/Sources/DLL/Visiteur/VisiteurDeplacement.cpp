#include "VisiteurDeplacement.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"



/// Constructeur par défaut.
VisiteurDeplacement::VisiteurDeplacement()
{
}

// Constructeur par paramètre.
VisiteurDeplacement::VisiteurDeplacement(const int& x, const int& y)
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