#include "VisiteurDuplication.h"
#include "FacadeModele.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"
#include <memory>


VisiteurDuplication::VisiteurDuplication()
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		if (table->chercher(i)->estSelectionne())
		{
			nNoeuds_++;
		}
	}
}

VisiteurDuplication::~VisiteurDuplication()
{
	
}

void VisiteurDuplication::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

void VisiteurDuplication::visiter(NoeudTable* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_DUPLICATION);
	noeud->ajouter(nouveauNoeud);
	referenceNoeud_ = nouveauNoeud.get();
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
	if (nNoeuds_ > 1)
	{
		nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative());
	}
	referenceNoeud_->ajouter(nouveauNoeud);
}


void VisiteurDuplication::visiter(NoeudMur* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_MUR);

	nouveauNoeud->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauNoeud->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	if (nNoeuds_ > 1)
	{
		nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative());
	}
	referenceNoeud_->ajouter(nouveauNoeud);
}


void VisiteurDuplication::visiter(NoeudLigne* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	//Créer une nouvelle ligne et assigner ses attributs.
	shared_ptr<NoeudAbstrait> nouvelleLigne = arbre->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);
	nouvelleLigne->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	if (nNoeuds_ > 1)
	{
		nouvelleLigne->assignerPositionRelative(noeud->obtenirPositionRelative());
	}
	//Créer une copie des segments.
	nouvelleLigne_ = nouvelleLigne.get();
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{		
		
	}
	referenceNoeud_->ajouter(nouvelleLigne);
}

void VisiteurDuplication::visiter(NoeudDuplication* noeud)
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
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
}


void VisiteurDuplication::visiter(NoeudSegment* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouveauSegment; 
	nouveauSegment = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
	nouveauSegment->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouveauSegment->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauSegment->assignerPositionRelative(noeud->obtenirPositionRelative());
	nouvelleLigne_->ajouter(nouveauSegment);
}
void VisiteurDuplication::visiter(NoeudJonction* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouveauSegment; 
	nouveauSegment = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
	nouveauSegment->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouveauSegment->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauSegment->assignerPositionRelative(noeud->obtenirPositionRelative());
	nouvelleLigne_->ajouter(nouveauSegment);
}