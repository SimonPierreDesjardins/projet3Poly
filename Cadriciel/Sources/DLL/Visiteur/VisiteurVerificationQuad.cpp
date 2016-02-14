///////////////////////////////////////////////////////////////////////////
/// @file VisiteurVerificationQuad.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurVerificationQuad.h"
#include "VisiteurMiseAJourQuad.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"

/// Constructeur par défaut.
VisiteurVerificationQuad::VisiteurVerificationQuad()
{
}

/// Destructeur.
VisiteurVerificationQuad::~VisiteurVerificationQuad()
{

}

void VisiteurVerificationQuad::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}


void VisiteurVerificationQuad::visiter(NoeudTable* noeud)
{
	objetsDansZoneSimulation_ = true;
	NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		enfant = noeud->chercher(i);
		enfant->accepterVisiteur(this);
	}
}

void VisiteurVerificationQuad::visiter(NoeudDuplication* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}


void VisiteurVerificationQuad::visiter(NoeudPoteau* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobantCourant().coins[i]);
	}
}

void VisiteurVerificationQuad::visiter(NoeudMur* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobantCourant().coins[i]);
	}
}

void VisiteurVerificationQuad::visiter(NoeudDepart* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobantCourant().coins[i]);
	}
}


void VisiteurVerificationQuad::visiter(NoeudLigne* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}


void VisiteurVerificationQuad::visiter(NoeudSegment* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobantCourant().coins[i]);
	}
}


bool VisiteurVerificationQuad::verifierPointEstSurTable(glm::dvec3 point)
{
	// Les valeurs maximales de la table.
	const int MIN_X = -48;
	const int MAX_X =  48;
	const int MIN_Y = -24;
	const int MAX_Y =  24;

	return MIN_X <= point.x && point.x <= MAX_X && MIN_Y <= point.y && point.y <= MAX_Y;
}