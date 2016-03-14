///////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteau.h
/// @author Frederic Gregoire
/// @date 2016-01-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDPOTEAU_H__
#define __ARBRE_NOEUDS_NOEUDPOTEAU_H__

#include "NoeudComposite.h"
#include "CercleEnglobant.h"
#include "GL/glew.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPoteau
/// @brief Noeud des obstacles au robot sous forme de poteaux
///
/// @author Frédéric Grégoire
/// @date 2016-01-20
///////////////////////////////////////////////////////////////////////////
class NoeudPoteau : public NoeudAbstrait
{

public:
	/// Constructeur
	NoeudPoteau(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPoteau();

    inline CercleEnglobant obtenirCercleEnglobant();

     
    virtual void animer(float dt);
	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:
    CercleEnglobant cercle_;
};
 
inline CercleEnglobant NoeudPoteau::obtenirCercleEnglobant()
{
    return cercle_;
}

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////