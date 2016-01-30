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
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		// TODO: à décommenter quand la sélection sera implémentée.
		//if (enfant->estSelectionne())
		{
			enfant->accepterVisiteur(this);
		}
	}
}


void VisiteurRotation::visiter(NoeudPoteau* noeud)
{
	assignerNouvellePositionRelative(noeud);
}


void VisiteurRotation::visiter(NoeudMur* noeud)
{
	// Assigner le nouvel angle de rotation.
	double angle = noeud->obtenirAngleRotation() + angleRotation_;
	noeud->assignerAngleRotation(angle);
	
	assignerNouvellePositionRelative(noeud);
}


void VisiteurRotation::visiter(NoeudLigneNoire* noeud)
{
	assignerNouvellePositionRelative(noeud);

	NoeudAbstrait* enfant;
	double angle;
	glm::dvec3 nouvellePositionRelative;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		//TODO: à mettre dans une méthode visiter pour un segment.
		enfant = noeud->chercher(i).get();
		utilitaire::calculerPositionApresRotation(enfant->obtenirPositionRelative(), nouvellePositionRelative, angleRotation_);
		enfant->assignerPositionRelative(nouvellePositionRelative);
		angle = enfant->obtenirAngleRotation() + angleRotation_;
		enfant->assignerAngleRotation(angle);
	}
}

void VisiteurRotation::calculerCentreSelection(NoeudAbstrait* noeud)
{
	NoeudAbstrait* enfant;
	int nSelections = 0;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i).get();
		//TODO: à décommenter quand la sélection sera implémentée.
		//if (enfant->estSelectionne())
		{
			centreSelection_ += enfant->obtenirPositionRelative();
			nSelections++;
		}
	}
	centreSelection_ /= nSelections;
	std::cout << "calcul centre selection:" << centreSelection_[0] << " : " << centreSelection_[1] << std::endl;
}

void VisiteurRotation::assignerNouvellePositionRelative(NoeudAbstrait* noeud)
{
	glm::dvec3 distanceCentreSelection = noeud->obtenirPositionRelative() - centreSelection_;
	glm::dvec3 nouvelleDistanceCentreSelection;
	utilitaire::calculerPositionApresRotation(distanceCentreSelection, nouvelleDistanceCentreSelection, angleRotation_);
	noeud->assignerPositionRelative(nouvelleDistanceCentreSelection + centreSelection_);
}
