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

