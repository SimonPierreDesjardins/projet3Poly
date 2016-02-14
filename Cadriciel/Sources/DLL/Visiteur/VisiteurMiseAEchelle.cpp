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
#include <iostream>

/// Constructeur par défaut.
VisiteurMiseAEchelle::VisiteurMiseAEchelle()
{

}

/// Destructeur.
VisiteurMiseAEchelle::~VisiteurMiseAEchelle()
{
}

void VisiteurMiseAEchelle::initialiser(ArbreRendu* noeud)
{
	facteursDimensionsInitiaux_.clear();
	NoeudAbstrait* table = noeud->chercher("table");
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		facteursDimensionsInitiaux_.push_back(table->chercher(i)->obtenirFacteurMiseAEchelle());
	}
}


void VisiteurMiseAEchelle::reinitialiser(ArbreRendu* noeud)
{
	NoeudAbstrait* table = noeud->chercher("table");
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->chercher(i)->assignerFacteurMiseAEchelle(facteursDimensionsInitiaux_[i]);
		std::cout << facteursDimensionsInitiaux_[i] << std::endl;
	}
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
	double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle() + facteurMiseAEchelle_;
	if (facteurMiseAEchelle >= 0)
	{
		noeud->assignerFacteurMiseAEchelle(facteurMiseAEchelle);
	}
}

void VisiteurMiseAEchelle::visiter(NoeudMur* noeud)
{
	double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle() + facteurMiseAEchelle_ * 2;
	if (facteurMiseAEchelle >= 0)
	{
		noeud->assignerFacteurMiseAEchelle(facteurMiseAEchelle);
	}
}