#include "NoeudDuplication.h"
#include "VisiteurAbstrait.h"


NoeudDuplication::NoeudDuplication(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	estDupliquable_ = false;
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