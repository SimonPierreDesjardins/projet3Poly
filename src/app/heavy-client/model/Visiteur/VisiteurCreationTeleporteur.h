///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationTeleporteur.h
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_CREATION_TELEPORTEUR_H
#define VISITEUR_CREATION_TELEPORTEUR_H

#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCreationTeleporteur
/// @brief Visiteur permettant d'initialiser la création d'un teleporteur
///
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
///////////////////////////////////////////////////////////////////////////
class VisiteurCreationTeleporteur : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurCreationTeleporteur();

	/// Destructeur.
	virtual ~VisiteurCreationTeleporteur();

	/// Creation de poteau sur l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
	/// Creation de poteau sur la table.
	virtual void visiter(NoeudTable* noeud);
};

#endif // VISITEUR_CREATION_TELEPORTEUR_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////