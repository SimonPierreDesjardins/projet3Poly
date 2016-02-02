#include "VisiteurDuplication.h"
#include "FacadeModele.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"
#include <memory>


VisiteurDuplication::VisiteurDuplication()
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	for (int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		if (table->chercher(0)->estSelectionne())
		{
			nNoeuds_++;
		}
	}
}


VisiteurDuplication::VisiteurDuplication(const int& x, const int& y)
{

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
	
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne())
		{
			noeud->chercher(i)->accepterVisiteur(this);
		}
	}
}

void VisiteurDuplication::visiter(NoeudPoteau* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_POTEAU);
	
	nouveauNoeud->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	
	if (nNoeuds_ > 1)
	{
		nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative());
	}
	
	referenceNoeud_->ajouter(nouveauNoeud);
}


void VisiteurDuplication::visiter(NoeudMur* noeud)
{
}


void VisiteurDuplication::visiter(NoeudLigneNoire* noeud)
{

}


void VisiteurDuplication::visiter(NoeudSegment* noeud)
{

}

void VisiteurDuplication::visiter(NoeudDuplication* noeud)
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	// Ajouter les noeuds 
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		table->ajouter(noeud->obtenirDuplication(i));
	}
	table->effacer(noeud);
}