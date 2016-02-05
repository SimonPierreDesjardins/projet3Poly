///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.h
/// @author Olivier St-Amour
/// @date 2016-02-03
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DEPLACEMENT_H
#define VISITEUR_DEPLACEMENT_H

#include "VisiteurAbstrait.h"

class VisiteurDeplacement : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurDeplacement();

	// Constructeur par paramètre.
	VisiteurDeplacement(const int& x, const int& y);

	/// Destructeur.
	virtual ~VisiteurDeplacement();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
};


#endif // VISITEUR_Deplacement

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////