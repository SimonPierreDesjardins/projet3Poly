#include "NoeudDupliquation.h"
#include "VisiteurAbstrait.h"


NoeudDupliquation::NoeudDupliquation(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	estDupliquable_ = false;
}

NoeudDupliquation::~NoeudDupliquation()
{
}

void NoeudDupliquation::afficherConcret() const
{
	NoeudComposite::afficherConcret();
}

void NoeudDupliquation::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}