///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAEchelle.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurMiseAEchelle.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"


/// Constructeur par défaut.
VisiteurMiseAEchelle::VisiteurMiseAEchelle()
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
	const double FACTEUR_ARBITRAIRE = 10.0;
	
	double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle();
	double nouveauFacteurMiseAEchelle = facteurMiseAEchelle + facteurMiseAEchelle_ / FACTEUR_ARBITRAIRE;
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

void VisiteurMiseAEchelle::visiter(NoeudLigne* noeud)
{
}