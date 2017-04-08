///////////////////////////////////////////////////////////////////////////
/// @file NoeudPiece.h
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDPIECE_H__
#define __ARBRE_NOEUDS_NOEUDPIECE_H__

#include "NoeudComposite.h"
#include "CercleEnglobant.h"
#include "RectangleEnglobant.h"
#include "GL/glew.h"
#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPiece
/// @brief Noeud des pieces
///
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
///////////////////////////////////////////////////////////////////////////
class NoeudPiece : public NoeudAbstrait
{

public:
	/// Constructeur
	NoeudPiece(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPiece();

    virtual RectangleEnglobant* obtenirFormeEnglobante();
    virtual const RectangleEnglobant* obtenirFormeEnglobante() const;

	virtual CercleEnglobant* obtenirCercleEnglobante();
	virtual const CercleEnglobant* obtenirCercleEnglobante() const;
     
	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);



private:
    CercleEnglobant cercleEnglobant_;
    virtual void mettreAJourFormeEnglobante();
	RectangleEnglobant rectangleEnglobant_;
	
};
 

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////