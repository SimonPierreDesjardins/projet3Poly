///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPaireTeleporteurs.h
/// @author DGI-INF2990
/// @date 2007-01-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPAIRETELEPORTEURS_H__
#define __ARBRE_NOEUDS_NOEUDPAIRETELEPORTEURS_H__


#include "NoeudComposite.h"

#include <vector>

class VisiteurAbstrait;
///////////////////////////////////////////////////////////////////////////
/// @class NoeudComposite
/// @brief Implantation d'un noeud du patron composite qui peut posséder
///        des enfants.
///
///        Cette classe implante les différentes fonctions relatives aux
///        enfants, comme l'ajout, le retrait, la recherche, etc.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudPaireTeleporteurs : public NoeudComposite
{
public:
	// Constructeur.
	NoeudPaireTeleporteurs(uint32_t id, const std::string& type = std::string{ "" });
    // Destructeur.
    ~NoeudPaireTeleporteurs();

	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

	virtual bool NoeudPaireTeleporteurs::ajouter(std::shared_ptr<NoeudAbstrait> enfant);
};


#endif // __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
