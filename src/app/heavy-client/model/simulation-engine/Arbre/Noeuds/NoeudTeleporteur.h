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
#include "RectangleEnglobant.h"
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
	NoeudTeleporteur(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudTeleporteur();

    virtual RectangleEnglobant* obtenirFormeEnglobante();
    virtual const RectangleEnglobant* obtenirFormeEnglobante() const;
     
    virtual void animer(float dt);
	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

	virtual void assignerTeleporteur(NoeudAbstrait* teleporteur);
	virtual NoeudTeleporteur* obtenirProchainTeleporteur();

	int getId();
	void setId(int id);

private:
    CercleEnglobant cercleEnglobant_;
	int idTeleporteur_;
    virtual void mettreAJourFormeEnglobante();
	RectangleEnglobant rectangleEnglobant_;
	NoeudTeleporteur* teleporteur_;
};
 

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////