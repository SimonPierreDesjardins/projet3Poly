#include "VisiteurDetectionLigne.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"

VisiteurDetectionLigne::VisiteurDetectionLigne()
{
}


VisiteurDetectionLigne::~VisiteurDetectionLigne()
{
}


void VisiteurDetectionLigne::visiter(ArbreRendu* noeud)
{
	ligneEstDetectee_ = false;
	noeud->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}


void VisiteurDetectionLigne::visiter(NoeudTable* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && !ligneEstDetectee_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
    capteur_->assignerLigneEstDetectee(ligneEstDetectee_);
}


void VisiteurDetectionLigne::visiter(NoeudLigne* noeud)
{
	bool capteurEstSurLigne = false;
	NoeudAbstrait* enfant = nullptr;
    unsigned int n = noeud->obtenirNombreEnfants();
	for (unsigned int i = 0; i < n && !ligneEstDetectee_; i++)
	{
		enfant = noeud->chercher(i);
        utilitaire::QuadEnglobant quad = enfant->obtenirQuadEnglobantCourant();
		capteurEstSurLigne = utilitaire::calculerPointEstDansQuad(positionCapteur_,
                                                                  quad);
		if (capteurEstSurLigne)
		{
			ligneEstDetectee_ = true; 
		}
	}
}