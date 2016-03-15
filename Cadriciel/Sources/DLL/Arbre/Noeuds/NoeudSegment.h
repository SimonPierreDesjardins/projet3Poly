///////////////////////////////////////////////////////////////////////////
/// @file NoeudLigne.h
/// @author Frederic Gregoire
/// @date 2016-01-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDSEGMENT_H__
#define __ARBRE_NOEUDS_NOEUDSEGMENT_H__

#include "NoeudComposite.h"
#include "GL/glew.h"
#include "CercleEnglobant.h"

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudSegment
/// @brief Chaque noeud de ce type représente un des segments qui composent une ligne noire.
/// Celles-ci se situent habituellement sous un objet de type NoeudLigne.
///
/// @author Frédéric Grégoire
/// @date 2016-01-20
///////////////////////////////////////////////////////////////////////////
class NoeudSegment : public NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudSegment(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudSegment();

    virtual void animer(float dt);

	/// Affiche le segment.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:
    RectangleEnglobant rectangleEnglobant_;

    void mettreAJourFormeEnglobante();
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////