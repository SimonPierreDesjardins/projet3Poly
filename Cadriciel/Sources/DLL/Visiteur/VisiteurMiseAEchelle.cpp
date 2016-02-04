#include "VisiteurMiseAEchelle.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"


/// Constructeur par défaut.
VisiteurMiseAEchelle::VisiteurMiseAEchelle()
{
}

// Constructeur par paramètre.
VisiteurMiseAEchelle::VisiteurMiseAEchelle(const int& x, const int& y)
{
}

/// Destructeur.
VisiteurMiseAEchelle::~VisiteurMiseAEchelle()
{
}

void VisiteurMiseAEchelle::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

void VisiteurMiseAEchelle::visiter(NoeudTable* noeud)
{
	NoeudAbstrait* enfant;
	glm::dvec3 positionVirtuelle;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne())
		{
			enfant->accepterVisiteur(this);
		}
	}
}

void VisiteurMiseAEchelle::visiter(NoeudPoteau* noeud)
{
	double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle();
	double nouveauFacteurMiseAEchelle = facteurMiseAEchelle + facteurMiseAEchelle_;
	if (nouveauFacteurMiseAEchelle < 0)
	{
		nouveauFacteurMiseAEchelle = 0;
	}
	noeud->assignerFacteurMiseAEchelle(nouveauFacteurMiseAEchelle);
}

void VisiteurMiseAEchelle::visiter(NoeudMur* noeud)
{
	double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle();
	double nouveauFacteurMiseAEchelle = facteurMiseAEchelle + facteurMiseAEchelle_;
	if (nouveauFacteurMiseAEchelle < 0)
	{
		nouveauFacteurMiseAEchelle = 0;
	}
	noeud->assignerFacteurMiseAEchelle(nouveauFacteurMiseAEchelle);
}

void VisiteurMiseAEchelle::visiter(NoeudLigneNoire* noeud)
{
}