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
		noeud->accepterVisiteur(this);
	}
}


void VisiteurDetectionLigne::visiter(NoeudLigne* noeud)
{
	bool capteurEstSurLigne = false;
	NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && !ligneEstDetectee_; i++)
	{
		enfant = noeud->chercher(i);
		capteurEstSurLigne = utilitaire::calculerPointEstDansQuad(positionCapteur_, enfant->obtenirQuadEnglobantCourant());
		if (capteurEstSurLigne)
		{
			ligneEstDetectee_ = true;
		}
	}
}

