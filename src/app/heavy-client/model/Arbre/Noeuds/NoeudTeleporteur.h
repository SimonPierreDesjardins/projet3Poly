///////////////////////////////////////////////////////////////////////////
/// @file NoeudTeleporteur.h
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDTELEPORTEUR_H__
#define __ARBRE_NOEUDS_NOEUDTELEPORTEUR_H__

#include "NoeudComposite.h"
#include "CercleEnglobant.h"
#include "GL/glew.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudTeleporteur
/// @brief Noeud des teleporteurs
///
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
///////////////////////////////////////////////////////////////////////////
class NoeudTeleporteur : public NoeudAbstrait
{

public:
	/// Constructeur
	NoeudTeleporteur(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudTeleporteur();

    virtual CercleEnglobant* obtenirFormeEnglobante();
    virtual const CercleEnglobant* obtenirFormeEnglobante() const;
     
    virtual void animer(float dt);
	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

	int getId();
	void setId(int id);

private:
    CercleEnglobant cercleEnglobant_;
	int idTeleporteur_;
    virtual void mettreAJourFormeEnglobante();
};
 

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////