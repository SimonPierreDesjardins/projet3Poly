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

class VisiteurMiseAEchelle : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurMiseAEchelle();

	/// Destructeur.
	virtual ~VisiteurMiseAEchelle();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
};


#endif // VISITEUR_MISE_A_ECHELLE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////