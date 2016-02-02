///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author Olivier St-Amour
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DUPLICATION_H
#define VISITEUR_DUPLICATION_H

#include "VisiteurAbstrait.h"
 
class VisiteurDuplication : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurDuplication();

	// Constructeur par paramètre.
	VisiteurDuplication(const int& x, const int& y);
	
	/// Destructeur.
	virtual ~VisiteurDuplication();

	/// Creation de poteau sur l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
	/// Creation de poteau sur la table.
	virtual void visiter(NoeudTable* noeud);
};


#endif // VISITEUR_DUPLICATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////