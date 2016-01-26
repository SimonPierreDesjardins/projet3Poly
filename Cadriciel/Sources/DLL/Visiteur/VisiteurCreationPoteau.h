///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationPoteau.h
/// @author Olivier St-Amour
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_CREATION_POTEAU_H
#define VISITEUR_CREATION_POTEAU_H

#include "VisiteurAbstrait.h"

class VisiteurCreationPoteau : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurCreationPoteau();

	// Constructeur par paramètre.
	VisiteurCreationPoteau(const int& x, const int& y);
	
	/// Destructeur.
	virtual ~VisiteurCreationPoteau();

	/// Creation de poteau sur l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
	/// Creation de poteau sur la table.
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
};


#endif // VISITEUR_CREATION_POTEAU_H

