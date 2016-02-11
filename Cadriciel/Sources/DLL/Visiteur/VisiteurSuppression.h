///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.h
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_SUPPRESSION_H
#define VISITEUR_SUPPRESSION_H

#include "VisiteurAbstrait.h"

class VisiteurSuppression : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurSuppression();

	// Constructeur par paramètre.
	VisiteurSuppression(const int& x, const int& y);

	/// Destructeur.
	virtual ~VisiteurSuppression();


	/// Parcours du noeudTable.
	virtual void visiter(NoeudTable* noeud);
};

#endif // VISITEUR_SUPPRESSION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////