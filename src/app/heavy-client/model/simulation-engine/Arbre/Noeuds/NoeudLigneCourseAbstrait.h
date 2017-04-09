///////////////////////////////////////////////////////////////////////////
/// @file NoeudLigneCourseAbstrait.h
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDLIGNECOURSEABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDLIGNECOURSEABSTRAIT_H__

#include "NoeudComposite.h"
#include "CercleEnglobant.h"
#include "RectangleEnglobant.h"
#include "GL/glew.h"
#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudLigneCourseAbstrait
/// @brief Noeud des lignes de la course
///
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
///////////////////////////////////////////////////////////////////////////
class NoeudLigneCourseAbstrait : public NoeudComposite
{

public:
	/// Constructeur
	NoeudLigneCourseAbstrait(uint32_t id, const std::string& typeNoeud = std::string{ "" });
	/// Destructeur.
	~NoeudLigneCourseAbstrait();

    virtual RectangleEnglobant* obtenirFormeEnglobante();
    virtual const RectangleEnglobant* obtenirFormeEnglobante() const;


	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);



private:
    virtual void mettreAJourFormeEnglobante();
	RectangleEnglobant rectangleEnglobant_;

	
};
 

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////