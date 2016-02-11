#include "VisiteurVerificationObjets.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"


/// Constructeur par défaut.
VisiteurVerificationObjets::VisiteurVerificationObjets()
{

}

/// Destructeur.
VisiteurVerificationObjets::~VisiteurVerificationObjets()
{

}

void VisiteurVerificationObjets::visiter(ArbreRendu* noeud)
{
	noeud->mettreAJourQuadEnglobant();
	noeud->chercher("table")->accepterVisiteur(this);
}


void VisiteurVerificationObjets::visiter(NoeudTable* noeud)
{
	objetsDansZoneSimulation_ = true;
	NoeudAbstrait* enfant = nullptr;
	for (int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		enfant = noeud->chercher(i);
		enfant->accepterVisiteur(this);
	}
}

void VisiteurVerificationObjets::visiter(NoeudDuplication* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}


void VisiteurVerificationObjets::visiter(NoeudPoteau* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobant().coins[i]);
	}
}

void VisiteurVerificationObjets::visiter(NoeudMur* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobant().coins[i]);
	}
}


void VisiteurVerificationObjets::visiter(NoeudLigneNoire* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}


void VisiteurVerificationObjets::visiter(NoeudSegment* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobant().coins[i]);
	}
}


bool VisiteurVerificationObjets::verifierPointEstSurTable(glm::dvec3 point)
{
	// Les valeurs maximales de la table.
	const int MIN_X = -48;
	const int MAX_X =  48;
	const int MIN_Y = -24;
	const int MAX_Y =  24;

	return MIN_X <= point.x && point.x <= MAX_X && MIN_Y <= point.y && point.y <= MAX_Y;
}