///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationLigne.h
/// @author Frederic Gregoire
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_CREATION_LIGNE_H
#define VISITEUR_CREATION_LIGNE_H

#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCreationLigne
/// @brief Visiteur permettant d'initialiser la cr�ation d'une ligne.
///
/// @author Olivier St-Amour
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurCreationLigne : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurCreationLigne();

	/// Destructeur.
	virtual ~VisiteurCreationLigne();

	/// Creation de poteau sur l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
	/// Creation de poteau sur la table.
	virtual void visiter(NoeudTable* noeud);
};


#endif // VISITEUR_CREATION_POTEAU_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
