///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAEchelle.h
/// @author Olivier St-Amour
/// @date 2016-02-03
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_MISE_A_ECHELLE_H
#define VISITEUR_MISE_A_ECHELLE_H

#include "VisiteurAbstrait.h"
#include <vector>

class VisiteurMiseAEchelle : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurMiseAEchelle();

	/// Destructeur.
	virtual ~VisiteurMiseAEchelle();

	void initialiser(ArbreRendu* arbre);
	void reinitialiser(ArbreRendu* arbre);
	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
private:
	std::vector<double> facteursDimensionsInitiaux_;
};


#endif // VISITEUR_MISE_A_ECHELLE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////