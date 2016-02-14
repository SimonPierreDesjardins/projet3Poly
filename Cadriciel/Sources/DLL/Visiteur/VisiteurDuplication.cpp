///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include "VisiteurDuplication.h"
#include "FacadeModele.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"
#include <memory>

VisiteurDuplication::VisiteurDuplication()
{
	NoeudAbstrait* noeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	calculerCentreSelection(noeud);
}

VisiteurDuplication::~VisiteurDuplication()
{
	
}

void VisiteurDuplication::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

void VisiteurDuplication::visiter(NoeudTable* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_DUPLICATION);
	noeud->ajouter(nouveauNoeud);

	duplication_ = nouveauNoeud.get();
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

void VisiteurDuplication::visiter(NoeudPoteau* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_POTEAU);
	
	nouveauNoeud->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	// Assigner la position à la table dans la duplication si il y a plus qu'un noeud.
	
	nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);

	duplication_->ajouter(nouveauNoeud);
}


void VisiteurDuplication::visiter(NoeudMur* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_MUR);

	nouveauNoeud->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauNoeud->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	// Assigner la position à la table dans la duplication si il y a plus qu'un noeud.

	nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);

	duplication_->ajouter(nouveauNoeud);
}


void VisiteurDuplication::visiter(NoeudLigne* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	// Creer une nouvelle ligne et assigner ses attributs.
	shared_ptr<NoeudAbstrait> nouvelleLigne = arbre->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);
	nouvelleLigne->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());

	nouvelleLigne->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);

	// Appeler le visiteur des enfants.
	nouvelleLigne_ = nouvelleLigne.get();
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{		
		noeud->chercher(i)->accepterVisiteur(this);
	}
	duplication_->ajouter(nouvelleLigne);
}

void VisiteurDuplication::visiter(NoeudDuplication* noeud)
{
	NoeudAbstrait* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	NoeudAbstrait* table = arbre->chercher("table");
	// Ajouter les noeuds sur la table, puis détruire la duplication.
	std::shared_ptr<NoeudAbstrait> enfant;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->obtenirDuplication(i);
		// Assigner la position relative du noeud à la table avant de l'ajouter.
		enfant->assignerPositionRelative(noeud->obtenirPositionRelative() + enfant->obtenirPositionRelative());
		table->ajouter(enfant);
	}
	table->effacer(noeud);
	arbre->accepterVisiteur(this);
}


void VisiteurDuplication::visiter(NoeudSegment* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	// Creer le nouveau segment et copier les attributs du segment.
	shared_ptr<NoeudAbstrait> nouveauSegment = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);	
	nouveauSegment->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouveauSegment->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauSegment->assignerPositionRelative(noeud->obtenirPositionRelative());
	
	nouvelleLigne_->ajouter(nouveauSegment);
}
void VisiteurDuplication::visiter(NoeudJonction* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	
	// Creer la nouvelle jonction et copier la position relative.
	shared_ptr<NoeudAbstrait> nouvelleJonction = arbre->creerNoeud(ArbreRenduINF2990::NOM_JONCTION);
	nouvelleJonction->assignerPositionRelative(noeud->obtenirPositionRelative());

	nouvelleLigne_->ajouter(nouvelleJonction);
}

void VisiteurDuplication::calculerCentreSelection(NoeudAbstrait* noeud)
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
		if (enfant->estSelectionne() && enfant->estDuplicable())
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
}
