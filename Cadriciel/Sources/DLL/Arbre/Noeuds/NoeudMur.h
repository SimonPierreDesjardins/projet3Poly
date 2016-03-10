///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.h
/// @author Frederic Gregoire
/// @date 2016-01-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDMUR_H__
#define __ARBRE_NOEUDS_NOEUDMUR_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudLigne
/// @brief Noeud des murs servant d'obstacles au robot.
///
/// @author Frédéric Grégoire
/// @date 2016-01-20
///////////////////////////////////////////////////////////////////////////
class NoeudMur : public NoeudAbstrait
{

public:

	/// Constructeur
	NoeudMur(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMur();

    inline RectangleEnglobant obtenirRectangleEngobant() const;

	/// Affiche la table.
    virtual void animer(const float& dt);
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:
    RectangleEnglobant rectangle_;
    
};

inline RectangleEnglobant NoeudMur::obtenirRectangleEngobant() const
{
    return rectangle_;
}

#endif /// __ARBRE_NOEUDS_NOEUDMUR_H_

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////