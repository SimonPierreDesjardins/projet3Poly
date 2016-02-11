#include "NoeudDuplication.h"
#include "VisiteurAbstrait.h"


NoeudDuplication::NoeudDuplication(const std::string& typeNoeud)
{

}

NoeudDuplication::~NoeudDuplication()
{
}

void NoeudDuplication::afficherConcret() const
{
	NoeudComposite::afficherConcret();
}

void NoeudDuplication::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}
/*
void NoeudDuplication::mettreAJourQuadEnglobantConcret()
{
	NoeudAbstrait* enfant;
	for (int i = 0; i < enfants_.size(); i++)
	{
		enfant = chercher(i);
		enfant->mettreAJourQuadEnglobant();
		quadEnglobant_ = enfant->obtenirQuadEnglobant();
		for (int i = 0; i < 4; i++)
		{
			quadEnglobant_.coins[i] += positionRelative_;
		}
		enfant->assignerQuadEnglobant(quadEnglobant_);
	}
}
*/