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

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCreationPoteau
/// @brief Visiteur permettant d'initialiser la cr�ation d'un poteau
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurCreationPoteau : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurCreationPoteau();

	/// Destructeur.
	virtual ~VisiteurCreationPoteau();

	/// Creation de poteau sur l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
	/// Creation de poteau sur la table.
	virtual void visiter(NoeudTable* noeud);
};

#endif // VISITEUR_CREATION_POTEAU_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////