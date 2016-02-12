///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationMur.h
/// @author Frederic Gregoire
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_CREATION_MUR_H
#define VISITEUR_CREATION_MUR_H

#include "VisiteurAbstrait.h"

class VisiteurCreationMur : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurCreationMur();

	/// Destructeur.
	virtual ~VisiteurCreationMur();

	/// Creation de poteau sur l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
	/// Creation de poteau sur la table.
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);

};


#endif // VISITEUR_CREATION_POTEAU_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
