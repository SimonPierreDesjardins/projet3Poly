#include "VisiteurRotation.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include <iostream>

VisiteurRotation::VisiteurRotation()
{
	NoeudAbstrait* noeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0).get();
	calculerCentreSelection(noeud);
	std::cout << "Centre: " << centreSelection_[0] << " : " << centreSelection_[1] << std::endl;
}


VisiteurRotation::VisiteurRotation(const int& x, const int& y)
	: VisiteurAbstrait(x, y)
{
}


VisiteurRotation::~VisiteurRotation()
{
}


void VisiteurRotation::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}


void VisiteurRotation::visiter(NoeudTable* noeud)
{
	std::shared_ptr<NoeudAbstrait> enfant;
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		//if (enfant->estSelectionne())
		{
			enfant->accepterVisiteur(this);
		}
	}
}


void VisiteurRotation::visiter(NoeudPoteau* noeud)
{
	glm::dvec3 nouvellePosition;
	utilitaire::calculerPositionApresRotation(noeud->obtenirPositionRelative() - centreSelection_, nouvellePosition, angleRotation_);
	noeud->assignerPositionRelative(nouvellePosition);
}


void VisiteurRotation::visiter(NoeudMur* noeud)
{
	glm::dvec3 nouvellePosition;
	double angle = noeud->obtenirAngleRotation() + angleRotation_;
	noeud->assignerAngleRotation(angle);
	utilitaire::calculerPositionApresRotation(noeud->obtenirPositionRelative() - centreSelection_, nouvellePosition, angleRotation_);
	noeud->assignerPositionRelative(nouvellePosition);
}


void VisiteurRotation::visiter(NoeudLigneNoire* noeud)
{
	double angle = noeud->obtenirAngleRotation() + angleRotation_;
	noeud->assignerAngleRotation(angle);
}

void VisiteurRotation::calculerCentreSelection(NoeudAbstrait* noeud)
{
	NoeudAbstrait* enfant;
	int nSelections = 0;
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i).get();
		//if (enfant->estSelectionne())
		{
			centreSelection_ += noeud->obtenirPositionRelative();
			nSelections++;
		}
	}
	centreSelection_ /= nSelections;
}