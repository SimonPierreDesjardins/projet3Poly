#include <iostream>
#include "VisiteurRotation.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"


VisiteurRotation::VisiteurRotation()
{
	NoeudAbstrait* noeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	calculerCentreSelection(noeud);
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
	NoeudAbstrait* enfant;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne())
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
	// Assigner le nouvel angle de rotation.)
	double angle = noeud->obtenirAngleRotation() + angleRotation_;
	noeud->assignerAngleRotation(angle);
	
	assignerNouvellePositionRelative(noeud);
}

void VisiteurRotation::visiter(NoeudDepart* noeud)
{
	// Assigner le nouvel angle de rotation.)
	double angle = noeud->obtenirAngleRotation() + angleRotation_;
	noeud->assignerAngleRotation(angle);

	assignerNouvellePositionRelative(noeud);
}

void VisiteurRotation::visiter(NoeudLigne* noeud)
{
	assignerNouvellePositionRelative(noeud);
	NoeudAbstrait* enfant;
	double angle;
	glm::dvec3 nouvellePositionRelative;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		//TODO: à mettre dans une méthode visiter pour un segment.
		enfant = noeud->chercher(i);
		utilitaire::calculerPositionApresRotation(enfant->obtenirPositionRelative(), nouvellePositionRelative, angleRotation_);
		enfant->assignerPositionRelative(nouvellePositionRelative);
		angle = enfant->obtenirAngleRotation() + angleRotation_;
		enfant->assignerAngleRotation(angle);
	}
}

void VisiteurRotation::calculerCentreSelection(NoeudAbstrait* noeud)
{
	if (noeud->obtenirNombreEnfants() < 1) return;
	// Initialiser les minimums et les maximums 
	double minX = 0;
	double maxX = 0;
	double minY = 0;
	double maxY = 0;
	double x = 0;
	double y = 0;
	bool estPremierSelectionne = true;
	NoeudAbstrait* enfant;
	// Trouver les min / max dans les positions des noeuds sur la table.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne())
		{
			x = enfant->obtenirPositionRelative()[0];
			y = enfant->obtenirPositionRelative()[1];

			if (x > maxX || estPremierSelectionne)
			{
				maxX = x;
			}
			if (x < minX || estPremierSelectionne)
			{
				minX = x;
			}
			if (y > maxY || estPremierSelectionne)
			{
				maxY = y; 
			}
			if (y < minY || estPremierSelectionne)
			{
				minY = y;
			}
			
			if (estPremierSelectionne)
			{
				estPremierSelectionne = false;
			}
		}
	}
	// Calculer et assigner la position relative à la ligne
	 centreSelection_= { (minX + maxX) / 2, (minY + maxY) / 2, 0 };
	 std::cout << "centre de selection: " << centreSelection_[0] << " : " << centreSelection_[1]<< std::endl;
}

void VisiteurRotation::assignerNouvellePositionRelative(NoeudAbstrait* noeud)
{
	glm::dvec3 distanceCentreSelection = noeud->obtenirPositionRelative() - centreSelection_;
	glm::dvec3 nouvelleDistanceCentreSelection;
	utilitaire::calculerPositionApresRotation(distanceCentreSelection, nouvelleDistanceCentreSelection, angleRotation_);
	noeud->assignerPositionRelative(nouvelleDistanceCentreSelection + centreSelection_);
}
